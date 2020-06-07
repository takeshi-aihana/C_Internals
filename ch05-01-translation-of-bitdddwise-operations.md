## ビット演算の翻訳

この C言語のコードを例にとります。これは何かの関数の中から抜粋したコードです：

```C
        int a = 4;
        int b = 8;
        int c = a | b;
        int d = b & c;
```

スタックにおけるローカル変数の位置はそれぞれ次のとおりです（ローカル変数については[ここ](/ch03-01-stack-and-local-variables.md)で説明しました）：

```
    a => -4 (%ebp)
    b => -8 (%ebp)
    c => -12 (%ebp)
    d => -16 (%ebp)
```

一時的な保管場所としてのレジスタの使い方については[ここ](/ch04-01-translation-of-arithmetic-operations.md#tempVaribaleUsage)で説明しました。

これが生成したアセンブリ言語のコードです：

```Unix Assembly
	movl	$4, -4(%ebp)
	movl	$8, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	-4(%ebp), %edx
	orl	%edx, %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	-8(%ebp), %edx
	andl	%edx, %eax
	movl	%eax, -16(%ebp)
```

生成したアセンブリ言語のコードにコメントを入れたものが、こちらです：

```Unix Assembly
# a = 4
	movl	$4, -4(%ebp)

# b = 8
	movl	$8, -8(%ebp)

# tmp = b
	movl	-8(%ebp), %eax

# tmp2 = a
	movl	-4(%ebp), %edx

# tmp = tmp | tmp2
	orl	%edx, %eax

# c = tmp
	movl	%eax, -12(%ebp)

# tmp = c
	movl	-12(%ebp), %eax

# tmp2 = b
	movl	-8(%ebp), %edx

# tmp = tmp & tmp2
	andl	%edx, %eax

# d = tmp
	movl	%eax, -16(%ebp)
```

（ローカル）変数の中身がそれぞれレジスタに移動され、ビット演算の命令（このサンプルの場合だと ``andl`` と ``olr``）を使用したあと、その結果をメモリに戻しています。

---

* [目次](/SUMMARY.md)

* [前へ](/ch04-01-translation-of-arithmetic-operations.md)

* [次へ](/ch06-01-translation-of-branch-statement.md)
