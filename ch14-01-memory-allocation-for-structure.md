## 構造体のメモリの確保

コードの中で、なにか構造体のオブジェクトを生成すると、コンパイラは「切れ目のない」連続したメモリをその構造体のデータ・メンバのために確保します。
確保するメモリのサイズは、「最低でも」全てのデータメンバのサイズを足したものになります。
その際にコンパイラは「パディング」を使用して、二つのデータ・メンバの間に未使用の領域を生成することができます。
この「パディング」は構造体のデータ・メンバに高速にアクセスできるようにメンバを配置するために行われるものです。
但し、パディングの動きを制御し、コンパイラを停止することで余分な領域を確保できます。
構造体のデータ・メンバには構造体のベースアドレスと構造体の中でのオフセットを使ってアクセスします。

それでは、これを例を使って見てみることにしましょう。

C言語のコード：

```C
struct data_struct
{
	int a;
	int b;
};

struct data_struct global_data;

int main(void)
{
	struct data_struct local_data;
	global_data.a = 10;
	global_data.b = 15;

	local_data.a = 25;
	local_data.b = 20;

	return 0;
}
```

これが生成したアセンブリ言語のコードです：

```asm
	.comm	global_data,8,4
	.text
	.globl	main
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$10, global_data
	movl	$15, global_data+4
	movl	$25, -8(%ebp)
	movl	$20, -4(%ebp)
	movl	$0, %eax
	leave
	ret
```

構造体の中のメンバに対するオフセットは、次のとおりです：

```
    a => 0
    b => 4
```

``global_data`` のメンバへのアクセス方法は、次のとおりです：

```
    global_data.a => global_data+0 （または単に global_data）
    global_data.b => global_data+4
```

``local_data`` のメンバへのアクセス方法は、次のとおりです：

```
    local_data.a => (ebp - 8) => -8(%ebp)
    local_data.b => (ebp - 4) => -4(%ebp)
```

``local_data`` はスタックの -8(%ebp) から %(%ebp) のメモリ空間に確保されます。
ローカル変数の確保については[ここ](/ch03-01-stack-and-local-variables.md)を参照して下さい。


### 構造体とパディング

コンパイラは構造体にある二つのデータ・メンバの間に空の領域をいくつか確保して、各メンバに高速にアクセスできるようにします。
これを「パディング」と呼びます。
メンバ同士の境界に確保される空の領域のサイズはランタイムで使用するプロセッサのアーキテクチャに依存します。

これを例を使って見てみることにしましょう。

```C
struct data_struct
{
	char a;
	int b;
};
```

i386 アーキテクチャの場合 ``sizeof()`` 演算子を使って、ここで定義した構造体のサイズを取得すると、8 が返ってきます。
しかし机上では ``sizeof(char)`` の返り値は 1、そして ``sizeof(int)`` の返り値は 4 なので合計は 5バイトのはずですが、コンパイラが実際に確保したのは 8バイトです。
すなわち ``char`` 型のメンバにも 4バイト確保されていたのです。

ここで構造体を次のように宣言してみます：

```C
struct data_struct
{
	char a;
	int b;
} __attribute__((packed));
```

すると i386 アーキテクチャの場合 ``sizeof(struct data_struct)`` の返り値は 5になります。
`` __attribute__((packed))`` はコンパイラにパディングしないよう強制して無駄な空き領域を確保しないようにします。
また ``__attribute__()`` は構造体の中にあるデータ・メンバごとに指定することも可能です。

例えば：

```C
struct data_struct
{
	char a;
	int b __attribute__((packed));
};
```

この宣言は構造体のデータ・メンバ ``a`` と ``b`` の間はパディングしないと言う意味です。
``__attribute__()`` は境界線を増やす際にも使用できます。
詳細についてはコンパイラのドキュメントを参照してみて下さい。

### 関数から構造体を返す

既に[ここ](/ch13-01-returning-value-from-function.md)で、基本データ型の場合は``eax`` レジスタを介して関数からの返り値を受け取ることを説明しました。
しかし構造体の場合は ``eax`` レジスタで返すことはできません。
なぜなら ``eax`` レジスタのサイズは 4バイト固定であり、構造体のサイズは任意だからです。
関数から構造体を返り値にするには、コンパイラが別の方法を使う必要があります。

それでは、このような時に ``gcc`` コンパイラがどのように動くか例を使って見てみることにしましょう：

```C
struct data_struct
{
	int a;
	int b;
};

struct data_struct
fun(void)
{
	struct data_struct data;
	data.a = 20;
	data.b = 25;
	return data;
}

int main (void)
{
	struct data_struct local_data = fun();
	return 0;
}
```

これが生成したアセンブリ言語のコードです：

```asm
	.text
	.globl	fun
fun:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$20, -8(%ebp)
	movl	$25, -4(%ebp)
	movl	8(%ebp), %ecx
	movl	-8(%ebp), %eax
	movl	-4(%ebp), %edx
	movl	%eax, (%ecx)
	movl	%edx, 4(%ecx)
	movl	8(%ebp), %eax
	leave
	ret	$4
	.globl	main
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	leal	-8(%ebp), %eax
	movl	%eax, (%esp)
	call	fun
	subl	$4, %esp
	movl	$0, %eax
	leave
	ret
```

このアセンブリ言語のコードと等価なC言語のプログラムを次のように作成し直すこともできます：

```C
void
fun(struct data_struct *ptr)
{
	struct data_struct data;
	data.a = 20;
	data.b = 25;
	ptr->a = data.a;
	ptr->b = data.b;
}

int main (void)
{
	struct data_struct data;
	fun(&data);
	return 0;
}
```

コンパイラは ``data`` を返す関数に構造体へのポインタを一つ渡します。
ここで注意したい点が二つあります。

* 構造体を返す関数の型は ``void`` とする。
すなわち ``eax`` レジスタ経由では構造体を返さない。

* 関数は構造体を指すポインタ型を引数として受け取る。

---

* [目次](/SUMMARY.md#C言語インターナル)

* [前へ](/ch13-01-returning-value-from-function.md)

* [次へ](/ch15-01-mixing-c-and-assenbly.md)
