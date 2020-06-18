## ループ処理の翻訳

#### <u>WHILE ループ</u>

この C言語のコードを例にとります。これは何かの関数の中から抜粋したコードです：

```C
	int a = 4;
	int b = 8;
	int d = 0;

	while (b > a) {
		d = a + 2;
		b--;
	}
```

これが生成したアセンブリ言語のコードです：

```asm
	movl	$4, -4(%ebp)
	movl	$8, -8(%ebp)
	movl	$0, -12(%ebp)
	jmp	.L2
.L3:
	movl	-4(%ebp), %eax
	addl	$2, %eax
	movl	%eax, -12(%ebp)
	subl	$1, -8(%ebp)
.L2:
	movl	-8(%ebp), %eax
	cmpl	-4(%ebp), %eax
	jg	.L3
```

スタックにおけるローカル変数の位置はそれぞれ次のとおりです（ローカル変数については[ここ](/ch03-01-stack-and-local-variables.md)で説明しました）：

```
    a => (ebp -  4) => -4(%ebp)
    b => (ebp -  8) => -8(%ebp)
    d => (ebp - 12) => -12(%ebp)
```

一時的な保管場所としてのレジスタの使い方については[ここ](/ch04-01-translation-of-arithmetic-operations.md#tempVaribaleUsage)で説明しました。

生成したアセンブリ言語のコードにコメントを入れたものが、こちらです：


```asm
# a = 4
# b = 8
# d = 0
	movl	$4, -4(%ebp)
	movl	$8, -8(%ebp)
	movl	$0, -12(%ebp)

# ラベル L2 へジャンプする
# WHILE ループの条件をラベル L2 で評価する
	jmp	.L2

# WHILE 文の中にあるループブロックの先頭
.L3:

# tmp = a
	movl	-4(%ebp), %eax

# tmp = tmp + 2
	addl	$2, %eax

# d = tmp
	movl	%eax, -12(%ebp)

# b = b - 1
	subl	$1, -8(%ebp)

# WHILE 文を開始したら、ここで条件を評価する
.L2:

# tmp = b
	movl	-8(%ebp), %eax

# a と tmp を比較する
	cmpl	-4(%ebp), %eax

# tmp が a よりも大きい場合はループのブロック（ラベル L3）へジャンプする
	jg	.L3
```

#### <u>FOR ループ</u>

この C言語のコードを例にとります：

```C
	int a = 4;
	int b = 8;
	int d = 0;

	for (b = 9; b > a; b--) {
		d = a + 2;
	}
```

これが生成したアセンブリ言語のコードです：

```asm
	movl	$4, -4(%ebp)
	movl	$8, -8(%ebp)
	movl	$0, -12(%ebp)
	movl	$9, -8(%ebp)
	jmp	.L2
.L3:
	movl	-4(%ebp), %eax
	addl	$2, %eax
	movl	%eax, -12(%ebp)
	subl	$1, -8(%ebp)
.L2:
	movl	-8(%ebp), %eax
	cmpl	-4(%ebp), %eax
	jg	.L3
```

生成したアセンブリ言語のコードの大部分は WHILE ループのそれと同じです。
ここには注目したい点を二つ紹介します：

* ループの初期条件をセットする命令が IF ブロック（比較命令）のコードよりも前に生成されている

* ループを更新していく命令が IF ブロック（比較命令）のコードの最後に生成されている

---

* [目次](/SUMMARY.md#C言語インターナル)

* [前へ](/ch06-01-translation-of-branch-statement.md#分岐処理の翻訳)

* [次へ](/ch08-01-pointer-dereferencing.md#ポインタの逆参照)
