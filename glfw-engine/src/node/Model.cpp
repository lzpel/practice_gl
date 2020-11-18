//
// Created by misum on 2020/11/15.
//

#include "Model.h"

#include "Graphics.h"

/// TODO 実装と宣言を分離
/// マクロ分岐によるTinyGLTFの隠蔽のため先にTinyGLTFをincludeする
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION
#define JSON_NOEXCEPTION

#include "tiny_gltf.h"

#undef TINYGLTF_IMPLEMENTATION
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

#include<stdio.h>


bool loadModel(tinygltf::Model &model, const char *filename) {
	tinygltf::TinyGLTF loader;
	std::string err;
	std::string warn;

	bool res = loader.LoadASCIIFromFile(&model, &err, &warn, filename) ||
	           loader.LoadBinaryFromFile(&model, &err, &warn, filename);
	if (!warn.empty()) {
		printf("WARN: %s\n", warn.c_str());
	}

	if (!err.empty()) {
		printf("ERR: %s\n", err.c_str());
	}

	if (!res)
		printf("Failed to load glTF: %s\n", filename);
	else
		printf("Loaded glTF: %s\n", filename);

	return res;
}

std::map<int, GLuint> bindMesh(std::map<int, GLuint> vbos,
                               tinygltf::Model &model, tinygltf::Mesh &mesh) {
	for (size_t i = 0; i < model.bufferViews.size(); ++i) {
		const tinygltf::BufferView &bufferView = model.bufferViews[i];
		if (bufferView.target == 0) {  // TODO impl drawarrays
			printf("WARN: bufferView.target is zero\n");
			continue;  // Unsupported bufferView.
			/*
			  From spec2.0 readme:
			  https://github.com/KhronosGroup/glTF/tree/master/specification/2.0
					   ... drawArrays function should be used with a count equal to
			  the count            property of any of the accessors referenced by the
			  attributes            property            (they are all equal for a given
			  primitive).
			*/
		}

		const tinygltf::Buffer &buffer = model.buffers[bufferView.buffer];
		printf("bufferview.target %d\n", bufferView.target);

		GLuint vbo;
		glGenBuffers(1, &vbo);
		vbos[i] = vbo;
		glBindBuffer(bufferView.target, vbo);

		printf("buffer.data.size = %d, bufferview.byteOffset = %d\n", buffer.data.size(), bufferView.byteOffset);

		glBufferData(bufferView.target, bufferView.byteLength,
		             &buffer.data.at(0) + bufferView.byteOffset, GL_STATIC_DRAW);
	}

	for (size_t i = 0; i < mesh.primitives.size(); ++i) {
		tinygltf::Primitive primitive = mesh.primitives[i];
		tinygltf::Accessor indexAccessor = model.accessors[primitive.indices];

		for (auto &attrib : primitive.attributes) {
			tinygltf::Accessor accessor = model.accessors[attrib.second];
			int byteStride =
					accessor.ByteStride(model.bufferViews[accessor.bufferView]);
			glBindBuffer(GL_ARRAY_BUFFER, vbos[accessor.bufferView]);

			int size = 1;
			if (accessor.type != TINYGLTF_TYPE_SCALAR) {
				size = accessor.type;
			}

			int vaa = -1;
			if (attrib.first.compare("POSITION") == 0) vaa = 0;
			if (attrib.first.compare("NORMAL") == 0) vaa = 1;
			if (attrib.first.compare("TEXCOORD_0") == 0) vaa = 2;
			if (vaa > -1) {
				glEnableVertexAttribArray(vaa);
				glVertexAttribPointer(vaa, size, accessor.componentType, accessor.normalized ? GL_TRUE : GL_FALSE,
				                      byteStride, BUFFER_OFFSET(accessor.byteOffset));
			} else {
				printf("vaa missing: %s\n", attrib.first.c_str());
			}
		}

		if (model.textures.size() > 0) {
			// fixme: Use material's baseColor
			tinygltf::Texture &tex = model.textures[0];

			if (tex.source > -1) {

				GLuint texid;
				glGenTextures(1, &texid);

				tinygltf::Image &image = model.images[tex.source];

				glBindTexture(GL_TEXTURE_2D, texid);
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

				GLenum format = GL_RGBA;

				if (image.component == 1) {
					format = GL_RED;
				} else if (image.component == 2) {
					format = GL_RG;
				} else if (image.component == 3) {
					format = GL_RGB;
				} else {
					// ???
				}

				GLenum type = GL_UNSIGNED_BYTE;
				if (image.bits == 8) {
					// ok
				} else if (image.bits == 16) {
					type = GL_UNSIGNED_SHORT;
				} else {
					// ???
				}

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0,
				             format, type, &image.image.at(0));
			}
		}
	}

	return vbos;
}

// bind models
void bindModelNodes(std::map<int, GLuint> vbos, tinygltf::Model &model,
                    tinygltf::Node &node) {
	if ((node.mesh >= 0) && (node.mesh < model.meshes.size())) {
		bindMesh(vbos, model, model.meshes[node.mesh]);
	}

	for (size_t i = 0; i < node.children.size(); i++) {
		assert((node.children[i] >= 0) && (node.children[i] < model.nodes.size()));
		bindModelNodes(vbos, model, model.nodes[node.children[i]]);
	}
}

GLuint bindModel(tinygltf::Model &model) {
	std::map<int, GLuint> vbos;
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	const tinygltf::Scene &scene = model.scenes[model.defaultScene];
	for (size_t i = 0; i < scene.nodes.size(); ++i) {
		assert((scene.nodes[i] >= 0) && (scene.nodes[i] < model.nodes.size()));
		bindModelNodes(vbos, model, model.nodes[scene.nodes[i]]);
	}

	glBindVertexArray(0);
	// cleanup vbos
	for (size_t i = 0; i < vbos.size(); ++i) {
		glDeleteBuffers(1, &vbos[i]);
	}

	return vao;
}

void drawMesh(tinygltf::Model &model, tinygltf::Mesh &mesh) {
	for (size_t i = 0; i < mesh.primitives.size(); ++i) {
		tinygltf::Primitive primitive = mesh.primitives[i];
		tinygltf::Accessor indexAccessor = model.accessors[primitive.indices];

		glDrawElements(primitive.mode, indexAccessor.count, indexAccessor.componentType, BUFFER_OFFSET(indexAccessor.byteOffset));
	}
}

// recursively draw node and children nodes of model
void drawModelNodes(tinygltf::Model &model, tinygltf::Node &node) {
	if ((node.mesh >= 0) && (node.mesh < model.meshes.size())) {
		drawMesh(model, model.meshes[node.mesh]);
	}
	for (size_t i = 0; i < node.children.size(); i++) {
		drawModelNodes(model, model.nodes[node.children[i]]);
	}
}

void drawModel(GLuint vao, tinygltf::Model &model) {
	glBindVertexArray(vao);

	const tinygltf::Scene &scene = model.scenes[model.defaultScene];
	for (size_t i = 0; i < scene.nodes.size(); ++i) {
		drawModelNodes(model, model.nodes[scene.nodes[i]]);
	}

	glBindVertexArray(0);
}

void dbgModel(tinygltf::Model &model) {
	for (auto &mesh : model.meshes) {
		printf("mesh : %s", mesh.name.c_str());
		for (auto &primitive : mesh.primitives) {
			const tinygltf::Accessor &indexAccessor =
					model.accessors[primitive.indices];

			printf("indexaccessor: count %d, type %d\n", indexAccessor.count, indexAccessor.componentType);

			tinygltf::Material &mat = model.materials[primitive.material];
			for (auto &mats : mat.values) {
				printf("mat : %s\n", mats.first.c_str());
			}

			for (auto &image : model.images) {
				printf("image name : %s\n", image.uri.c_str());
				printf("  size : %s\n", image.image.size());
				printf("  w/h : %d/%d\n", image.width, image.height);
			}

			printf("indices : %d\n", primitive.indices);
			printf("mode     : (%d)\n", primitive.mode);

			for (auto &attrib : primitive.attributes) {
				printf("attribute : %s\n", attrib.first.c_str());
			}
		}
	}
}

Model::Model(const char *filename) {
	loadModel(model, filename);
}

Model::~Model() {

}

void Model::Init() {
	vao = bindModel(model);
}

void Model::Draw() {
	drawModel(vao, model);
}

void Model::Terminate() {

}