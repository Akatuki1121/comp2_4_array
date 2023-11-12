#include "CppUnitTest.h"

#include "../include/lib_func.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTestSize)
	{
	public:

		TEST_METHOD(NULLのアドレスで初期化)
		{
			initialize(NULL, 1);						// NULLを渡す（通ればOK）
		}

		TEST_METHOD(要素数0でサイズを取得)
		{
			my_array ar;
			initialize(&ar, 0);						// -1要素(おかしな値)
			Assert::AreEqual(0, size(&ar));				// 要素数は0
			release(&ar);
		}

		TEST_METHOD(要素数1でサイズを取得)
		{
			my_array ar;
			initialize(&ar, 1);							// 1要素
			Assert::AreEqual(1, size(&ar));				// 要素数は１
			release(&ar);
		}

		TEST_METHOD(要素数1000000000でサイズを取得)
		{
			my_array ar;
			initialize(&ar, 1000000000);				// 要素1000000000
			Assert::AreEqual(1000000000, size(&ar));	// 要素数は1000000000
			release(&ar);
		}
	};

	TEST_CLASS(UnitTestSetGet)
	{
	public:
		TEST_METHOD(要素数1で1番目に値を設定)
		{
			my_array ar;
			initialize(&ar, 1);							// 1要素
			Assert::AreEqual(true, set(&ar, 0, 0));		// 要素0に設定できる
			Assert::AreEqual(0, get(&ar, 0));			// ar.addr[0]を取得
			release(&ar);
		}

		TEST_METHOD(要素数1なら2番目に値を設定できない)
		{
			my_array ar;
			initialize(&ar, 1);							// 1要素
			Assert::AreEqual(false, set(&ar, 1, 1));	// 要素1に設定できない
			Assert::AreEqual(0, get(&ar, 1));			// ar.addr[1]を取得(0)
			release(&ar);
		}

		TEST_METHOD(要素数1なら0番目に値を設定できない)
		{
			my_array ar;
			initialize(&ar, 1);							// 1要素
			Assert::AreEqual(false, set(&ar, -1, 1));	// 要素-1に設定できない
			Assert::AreEqual(0, get(&ar, -1));			// ar.addr[-1]を取得(0)
			release(&ar);
		}

		TEST_METHOD(要素数2で2番目に値を設定)
		{
			my_array ar;
			initialize(&ar, 2);							// 2要素
			Assert::AreEqual(true, set(&ar, 1, 3));		// 要素1に設定できる
			Assert::AreEqual(3, get(&ar, 1));			// ar.addr[1]を取得
			release(&ar);
		}

		TEST_METHOD(要素数2なら3番目に値を設定できない)
		{
			my_array ar;
			initialize(&ar, 2);							// 2要素
			Assert::AreEqual(false, set(&ar, 3, 2));	// 要素3に設定できない
			Assert::AreEqual(0, get(&ar, 3));			// ar.addr[3]を取得(0)
			release(&ar);
		}

		TEST_METHOD(要素数2ならー1番目に値を設定できない)
		{
			my_array ar;
			initialize(&ar, 2);							// 2要素
			Assert::AreEqual(false, set(&ar, -2, 1));	// 要素-2に設定できない
			Assert::AreEqual(0, get(&ar, -2));			// ar.addr[-2]を取得(0)
			release(&ar);
		}

		TEST_METHOD(要素数100000で100000番目に値を設定)
		{
			my_array ar;
			initialize(&ar, 100000);						// 100000要素
			Assert::AreEqual(true, set(&ar, 99999, 12345));	// 要素99999に設定できる
			Assert::AreEqual(12345, get(&ar, 99999));		// ar.addr[99999]を取得
			release(&ar);
		}

		TEST_METHOD(要素数100000で順番に値を設定)
		{
			my_array ar;
			initialize(&ar, 100000);					// 100000要素
			for (int i = 0; i < 100000; i++) {
				Assert::AreEqual(true, set(&ar, i, -i));// 要素に値を設定できる
			}
			for (int i = 0; i < 100000; i++) {
				Assert::AreEqual(-i, get(&ar, i));		// ar.addr[i]を取得
			}
			release(&ar);
		}
	};

	TEST_CLASS(UnitTestResize)
	{
	public:

		TEST_METHOD(要素数1から要素数10にサイズを変更)
		{
			my_array ar;
			initialize(&ar, 1);					// 1要素
			Assert::AreEqual(1, size(&ar));		// 要素数は1
			resize(&ar, 10);					// 要素数10に変更
			Assert::AreEqual(10, size(&ar));	// 要素数は10
			release(&ar);
		}

		TEST_METHOD(要素数1から要素数10にサイズを変更して値も確認)
		{
			my_array ar;
			initialize(&ar, 1);						// 1要素
			Assert::AreEqual(1, size(&ar));			// 要素数は１
			Assert::AreEqual(true, set(&ar, 0, 2));	// 要素0に設定できる
			Assert::AreEqual(false, set(&ar, 1, 3));// 要素1に設定できない
			resize(&ar, 10);						// 要素数10に変更
			Assert::AreEqual(10, size(&ar));		// 要素数は10
			Assert::AreEqual(2, get(&ar, 0));		// ar.addr[0]を取得
			Assert::AreEqual(true, set(&ar, 1, 3));	// 要素1に設定できる
			release(&ar);
		}

		TEST_METHOD(要素数10から要素数1にサイズを変更)
		{
			my_array ar;
			initialize(&ar, 10);					// 10要素
			Assert::AreEqual(10, size(&ar));		// 要素数は10
			resize(&ar, 1);							// 要素数1に変更
			Assert::AreEqual(1, size(&ar));			// 要素数は1
			release(&ar);
		}
		TEST_METHOD(要素数10から要素数1にサイズを変更して値も確認)
		{
			my_array ar;
			initialize(&ar, 10);					// 10要素
			Assert::AreEqual(10, size(&ar));		// 要素数は10
			for (int i = 0; i < 10; i++) {
				Assert::AreEqual(true, set(&ar, i, 10 - i));// 値を入れる
			}
			resize(&ar, 1);							// 要素数1に変更
			Assert::AreEqual(1, size(&ar));			// 要素数は1
			Assert::AreEqual(10, get(&ar, 0));		// ar.addr[0]を取得
			Assert::AreEqual(0, get(&ar, 1));		// ar.addr[1]を取得(0)
			Assert::AreEqual(true, set(&ar, 0, 3));	// 要素0に設定できる
			release(&ar);
		}

		TEST_METHOD(要素数1から要素数1000000000にサイズを変更)
		{
			my_array ar;
			initialize(&ar, 1);										// 1要素
			Assert::AreEqual(1, size(&ar));							// 要素数は1
			Assert::AreEqual(true, set(&ar, 0, -10));				// 要素0に設定できる
			Assert::AreEqual(false, set(&ar, 1, 2));				// 要素1に設定できない
			resize(&ar, 1000000000);								// 要素数1000000000に変更
			Assert::AreEqual(1000000000, size(&ar));				// 要素数は1000000000
			Assert::AreEqual(-10, get(&ar, 0));						// ar.addr[0]を取得
			Assert::AreEqual(true, set(&ar, 1, 3));					// 要素1に設定できる
			Assert::AreEqual(3, get(&ar, 1));						// ar.addr[1]を取得
			Assert::AreEqual(true, set(&ar, 999999999, 1000000000));// 要素999999999に設定できる
			Assert::AreEqual(1000000000, get(&ar, 999999999));		// ar.addr[999999999]を取得
			Assert::AreEqual(0, get(&ar, 1000000000));				// ar.addr[1000000000]を取得(0)
			release(&ar);
		}
	};
}