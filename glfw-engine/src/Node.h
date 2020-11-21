//
// Created by misum on 2020/11/15.
//

#ifndef GLPRACTICE_NODE_H
#define GLPRACTICE_NODE_H

#include<list>
#include<map>
#include<string>
class Node{
public:
	struct Stat{
		int x,y,time,frq;
		signed shader;
		const char* text;
		Node* node;
	};
	float pos[3];
	const char* name;
private:
	Node* parent;
	std::map<std::string,Stat> *status;
	std::list<Node*> children;
public:
	///@fn
	/// 最上位を含む限られたNodeは状態を持ちステートマシンと呼ぶ。
	/// 全てのノードは親を遡り最初のステートマシンの状態のみ参照できる。
	/// ステートマシンがゲームの進行を管理する。
	/// gitコマンドが直近の親ディレクトリの.gitを参照する仕組みを模倣している
	Node(bool isStateMachine=false);
	virtual ~Node();
	///@fn
	/// 描画要素を追加する。
	/// 子供のInit()を呼ぶ。
	/// Nodeはメモリ解放について責任を持つため関数名は子供がnewで確保されるべきことを意味している。
	/// 最上位以外は自分自身ではなく親からInitを呼ばれるのでNodeInitは存在しない。
	void NodeNew(Node*newchild);
	///@fn
	/// 親子関係を破棄し一族郎党自壊。
	void NodeTerminate();
	///@fn
	/// 自分自身と子孫を描画する
	void NodeDraw();
	///@fn
	/// 子供を検索する
	Node* NodeFind(const char* key);
	///@fn
	/// 親を遡り状態を取得する。
	Stat& NodeState(const char* key,bool apex=false);
	void NodeState(const char* key,int x,int y);//後で捨てる、一つに一つの変数
public:
	void Move(float x,float y,float z);
private:
	/// @fn
	/// 描画要素の初期化を行う。
	///　Terminate と対
	virtual void Init()=0;
	/// @fn
	/// 描画要素の描画を行う。
	virtual void Draw()=0;
	/// @fn
	/// 描画要素の破棄を行う。
	virtual void Terminate()=0;
};

#endif //GLPRACTICE_NODE_H
