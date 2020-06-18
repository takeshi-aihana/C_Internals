## ポインタの逆参照

この C言語のコードを例にとります：

```C
// これはグローバル宣言
int globalVar;

void f(void)
{
	int b;
	int *ptr;

	ptr = &globalVar;
	*ptr = 100;
	b = *ptr;
}
```

これが生成したアセンブリ言語のコードです：

```asm
	movl	$globalVar, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	$100, (%eax)
	movl	-4(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -8(%ebp)
```

スタックにおけるローカル変数の位置はそれぞれ次のとおりです（ローカル変数については[ここ](/ch03-01-stack-and-local-variables.md)で説明しました）：

```
    ptr => (ebp - 4) => -4(%ebp)
    b   => (ebp - 8) => -8(%ebp)
```

一時的な保管場所としてのレジスタの使い方については[ここ](/ch04-01-translation-of-arithmetic-operations.md#tempVaribaleUsage)で説明しました。

生成したアセンブリ言語のコードにコメントを入れたものが、こちらです：

```asm
# ptr = &globalVar
	movl	$globalVar, -4(%ebp)

# tmp = ptr
	movl	-4(%ebp), %eax

# *tmp = 100
	movl	$100, (%eax)

# tmp = ptr
	movl	-4(%ebp), %eax

# tmp = *tmp
	movl	(%eax), %eax

# b = tmp
	movl	%eax, -8(%ebp)
```

---

* [目次](/SUMMARY.md#C言語インターナル)

* [前へ](/ch07-01-translation-of-loop.md#ループ処理の翻訳)

* [次へ](/ch09-01-array-indexing.md#配列の操作)
