// Null 6.9.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//


#include <iostream>
#include <memory>
#include <assert.h>


// 武器クラス（親クラス）
class Weapon {
public:
	// virtual を付けることで 子クラス側で関数を上書きする
	virtual void Use() {
		std::cout << "Weapon Attack!" << std::endl;
	}
};

// 剣クラス（Weapon を継承する）
class Sword : public Weapon {

public:
	// override 「親クラスの関数を上書きしています」ということ
	void Use() override {
		std::cout << "Sword Slash!" << std::endl;
	}
};

// プレイヤークラス
class Player {
	// shared_ptr　自動でメモリ管理をしてくれるスマートポインタ
	std::shared_ptr<Weapon> weapon;

public:
	
	// コンストラクタ
	// weapon1 を受け取る
	Player(std::shared_ptr<Weapon> weapon1)
		// std::move を使うことで weapon1 の所有権を weapon に移動する
	
		// コピーではないので 無駄な参照カウント増加を防げる
		: weapon(std::move(weapon1))
	{
		std::cout << "Player Constructor" << std::endl;
	
		// move後の参照カウント確認
		// weapon 側
		// 所有権を持っているので 1
		std::cout << "weapon use_count : "
			<< weapon.use_count()
			<< std::endl;


		// weapon1 側
		// moveされたので nullptr 状態
		// use_count は 0
		std::cout << "weapon1 use_count : "
			<< weapon1.use_count()
			<< std::endl;
	}
	
	// 攻撃関数
	void Attack() {
		
		weapon->Use();// weapon の Use() を実行
	}
};

int main() {
	
	// Swordオブジェクト生成
	// make_shared を使うことで shared_ptr を安全に生成できる
	auto sword = std::make_shared<Sword>();
	
	// move前の参照カウント確認
	std::cout << "Before move" << std::endl;

	// 現在 sword だけが所有しているので 1
	std::cout << "sword : "
		<< sword.use_count()
		<< std::endl;
	
	// 所有権を Player に移動
	// std::move を使うことで
	// sword の所有権を p1 に渡す
	Player p1(std::move(sword));
	
	// move後の確認
	std::cout << "After move" << std::endl;

	// move後なので sword は nullptr
	// use_count は 0
	std::cout << "sword : "
		<< sword.use_count()
		<< std::endl;

	// sword が nullptr か確認
	// move後は中身が空になる
	if (sword == nullptr) {
		std::cout << "sword is nullptr" << std::endl;
	}
	
	// プレイヤー攻撃
	// Player が所有している weapon を使用
	p1.Attack();
	return 0;
}









/*
#include <iostream>
#include<assert.h>


class Weapon {
public:
	void Use(){}
};

class Player {
	std::shared_ptr<Weapon>weapon;
public:
	Player(std::shared_ptr<Weapon>weapon1):weapon(weapon1) 
		// weapos(std::move(weapon1)) std::move（ムーブポインタ）を消すことで無駄な参照カウントを増やさない
	{
		std::cout << weapon.use_count() << std::endl;
		std::cout << weapon1.use_count() << std::endl;
	}


	void Attack() {
	//	if (weapon)weapon->Use();  if分いらない
		weapon->Use();
	}
};

int main() {
	// 演習①　ムーブとコピーの拳動確認
	auto a = std::make_shared<Player>(std::make_shared<Weapon>());

	std::cout << "a:" << a.use_count() << std::endl;

	auto b = a;

	std::cout << "a:" << a.use_count() << std::endl;
	std::cout << "b:" << b.use_count() << std::endl;

	auto c = std::move(a);

	std::cout << "a:" << a.use_count() << std::endl;
	std::cout << "b:" << b.use_count() << std::endl;
	std::cout << "c:" << c.use_count() << std::endl;

//	return 0;

	assert(a != nullptr);
	a->Attack();



}
*/

/*
// 以下のは、メインに入ってたコード
auto wp = std::make_shared<Weapon>();

	// コピー（参照カウント+1）
	Player p(wp);
	
	// ムーブ（所有権を移動）これ使うと効率が良い
	Player q(std::move(wp));

	return 0;
*/


/*
// nullを使わないコード
#include <iostream>
#include<assert.h>

class Test
{
public:
	void Show()
	{
		std::cout << "Hello,World!!" << std::endl;
	}
};

void Func(Test* test)
{
	assert(test != nullptr);
	test->Show();
}

int main()
{
	Func(new Test());
	Func(nullptr);

	/*
	// nullを使ったコード
	auto p=nem Test();
	if(p!=nullptr){
	p->Show();
	}
	delete p;
	
}
*/
