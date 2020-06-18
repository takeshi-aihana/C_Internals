## 配列の操作

この C言語のコードを例にとります：

```C
// これはグローバル宣言
int globalVar[5];

void f(void)
{
	int b;
	int localArr[5];

	globalVar[2] = 12;
	localArr[0] = 3;
	localArr[4] = 18;
	b = localArr[4];
}
```

これが生成したアセンブリ言語のコードです：

```asm
	movl	$12, globalVar+8
	movl	$3, -24(%ebp)
	movl	$18, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	%eax, -4(%ebp)
```

スタックにおけるローカル変数の位置はそれぞれ次のとおりです（ローカル変数については[ここ](/ch03-01-stack-and-local-variables.md)で説明しました）：

```
    b        => (ebp -  4) => -4(%ebp)
    localArr => (ebp - 24) から (ebp - 4) => -24(%ebp) から -4(%ebp) [但し -4(%ebp) が指すメモリは含まれない]

         配列 localArr のサイズは 5
         この配列の１要素のサイズは 4バイト
         従って配列 localArr[] は合計 20バイト
```

一時的な保管場所としてのレジスタの使い方については[ここ](/ch04-01-translation-of-arithmetic-operations.md#tempVaribaleUsage)で説明しました。

生成したアセンブリ言語のコードにコメントを入れたものが、こちらです：

```asm
# globalVar[2] = 12
# (globalVar + 8) は globalVar 変数の先頭から 8バイト目を示す
# この配列の要素は 4バイトなので三番目の要素はバイト・オフセット 8から始まる
	movl	$12, globalVar+8

# localArr[0] =3
# localArr 変数は -24(%ebp) から始まるので localArr[0] のバイト・オフセットは 0
	movl	$3, -24(%ebp)

# localArr[4] = 18
# localArr[4] はバイトオフセット 16（-24 + 16 = -8）
	movl	$18, -8(%ebp)

# tmp = localArr[4]
	movl	-8(%ebp), %eax

# b = tmp
	movl	%eax, -4(%ebp)
```

### ポインタを使った配列の操作


この C言語のコードを例にとります：

```C
// これはグローバル宣言
int globalVar[5];

void f(void)
{
	int b;
	int *ptr = globalVar;

	b = ptr[4];
}
```

これが生成したアセンブリ言語のコードです：

```asm
	movl	$globalVar, -8(%ebp)
	movl	-8(%ebp), %eax
    addl    $16, %eax
	movl	(%eax), %eax
	movl	%eax, -4(%ebp)
```

スタックにおけるローカル変数の位置はそれぞれ次のとおりです（ローカル変数については[ここ](/ch03-01-stack-and-local-variables.md)で説明しました）：

```
    b   => (ebp - 4) => -4(%ebp)
    ptr => (ebp - 8) => -8(%ebp)
```

一時的な保管場所としてのレジスタの使い方については[ここ](/ch04-01-translation-of-arithmetic-operations.md#tempVaribaleUsage)で説明しました。

生成したアセンブリ言語のコードにコメントを入れたものが、こちらです：

```asm
# ptr = globalVar
	movl	$globalVar, -8(%ebp)

# tmp = ptr
    movl	-8(%ebp), %eax

# tmp = tmp + 16
# 現在 'tmp' にはポインタが格納されているので、次の命令はそのポインタを 16バイト移動する
    addl    $16, %eax

# tmp = *tmp
    movl	(%eax), %eax

# b = tmp
    movl	%eax, -4(%ebp)
```

---

* [目次](/SUMMARY.md#C言語インターナル)

* [前へ](/ch08-01-pointer-dereferencing.md)

* [次へ](/ch10-01-function-pointer.md)
