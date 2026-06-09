// Null 6.9.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//


#include <iostream>
#include <memory>
#include <assert.h>


class Weapon {

public:

	virtual void Use() {

		std::cout << "Weapon Attack!" << std::endl;

	}

};
// 演習②　ムーブを用いた所有権の転送
class Sword : public Weapon {

public:

	void Use() override {

		std::cout << "Sword Slash!" << std::endl;

	}

};

class Player {

	std::shared_ptr<Weapon> weapon;

public:

	// ムーブで受け取る
	Player(std::shared_ptr<Weapon> weapon1): weapon(std::move(weapon1))

	{

		std::cout << "Player Constructor" << std::endl;

		std::cout << "weapon use_count : "
			<< weapon.use_count()
			<< std::endl;

		std::cout << "weapon1 use_count : "
			<< weapon1.use_count()
			<< std::endl;

	}

	void Attack() {

		weapon->Use();

	}

};

int main() {

	auto sword = std::make_shared<Sword>();

	std::cout << "Before move" << std::endl;

	std::cout << "sword : "<< sword.use_count()<< std::endl;

	// 所有権を移動
	Player p1(std::move(sword));

	std::cout << "After move" << std::endl;

	std::cout << "sword : "
		<< sword.use_count()
		<< std::endl;



	// move後は nullptr になる
	if (sword == nullptr) {

		std::cout << "sword is nullptr" << std::endl;

	}

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
