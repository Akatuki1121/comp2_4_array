#pragma once // インクルードガード

// C++ でCのライブラリを使うときのおまじない
#ifdef __cplusplus
extern "C" {
#endif

	typedef struct
	{
		int num;
		int* addr;
	} my_array;

	// my_array を要素数nで初期化する
	void initialize(my_array* ar, int n);

	// my_array を解放する
	void release(my_array* ar);

	// my_array の要素数を変更する(以前の値は要素が同じ範囲で残す)
	void resize(my_array* ar, int n);

	// my_array のindex番目の要素にvalを設定する
	// index が確保されていない場所を指していたら返り値をfalseにする（設定出来たらtrue）
	bool set(my_array* ar, int index, int val);

	// my_array のindex番目の要素を取得する
	// index が確保されていない場所を指していたら0を返す
	int get(const my_array* ar, int index);

	// my_array の要素数を取得する
	int size(const my_array* ar);

	// C++ でCのライブラリを使うときのおまじない
#ifdef __cplusplus
} // extern "C"
#endif
