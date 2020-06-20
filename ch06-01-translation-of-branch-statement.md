## 分岐処理の翻訳

#### <u>IF-ELSE 文</u>

この C言語のコードを例にとります。これは何かの関数の中から抜粋したコードです：

```C
	int a = 4;
	int b = 8;
	int d = 0;

	if (a > b) {
		d = 1;
	}
	else {
		d = 2;
	}
```

そして生成したアセンブリ言語のコードが、こちら：

```asm
	movl	$4, -4(%ebp)
	movl	$8, -8(%ebp)
	movl	$0, -12(%ebp)
	movl	-4(%ebp), %eax
	cmpl	-8(%ebp), %eax
	jle	.L2
	movl	$1, -12(%ebp)
	jmp	.L1
.L2:
	movl	$2, -12(%ebp)
.L1:
```

スタックにおけるローカル変数の位置はそれぞれ次のとおりです（ローカル変数については[ここ](/ch03-01-stack-and-local-variables.md#スタックとローカル変数)で説明しました）：

```
    a => (ebp -  4) => -4(%ebp)
    b => (ebp -  8) => -8(%ebp)
    d => (ebp - 12) => -12(%ebp)
```

一時的な保管場所としてのレジスタの使い方については[ここ](/ch04-01-translation-of-arithmetic-operations.md#算術演算の翻訳)で説明しました。

生成したアセンブリ言語のコードにコメントを入れたものが、こちらです：

```asm
# a = 4
	movl	$4, -4(%ebp)

# b = 8
	movl	$8, -8(%ebp)

# d = 0
	movl	$0, -12(%ebp)

# tmp = a
	movl	-4(%ebp), %eax

# b と tmp を比較する
	cmpl	-8(%ebp), %eax

# もし tmp が b よりも小さいかまたは等しい場合は
# ラベル L2 （C言語のコードで言うと else ブロック）へジャンプする
	jle	.L2

# ここから if ブロック
# d = 1
	movl	$1, -12(%ebp)

# ここが if ブロックの最後の命令
# else ブロックの先にある命令（ラベル L1）へジャンプする
	jmp	.L1

# ここから else ブロック（ラベル L2）
.L2:

# d = 2
	movl	$2, -12(%ebp)

# ここで else ブロックは終了
# ここが else ブロック直後の命令
.L1:
```

#### <u>SWITCH-CASE 文</u>

この C言語のコードを例にとります。これは何かの関数の中から抜粋したコードです：

```C
	int a = 4;
	int b = 8;
	int d = 0;

	switch (b) {
	case 2:
		a++;
		break;
	case 8:
		b++;
		break;
	default:
		d++;
		break;
	}
```

そして生成したアセンブリ言語のコードが、こちら：

```asm
	movl	$4, -4(%ebp)
	movl	$8, -8(%ebp)
	movl	$0, -12(%ebp)
	movl	-8(%ebp), %eax
	cmpl	$2, %eax
	je	.L3
	cmpl	$8, %eax
	je	.L4
	jmp	.L6
.L3:
	addl	$1, -4(%ebp)
	jmp	.L1
.L4:
	addl	$1, -8(%ebp)
	jmp	.L1
.L6:
	addl	$1, -12(%ebp)
.L1:
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

# tmp = b
	movl	-8(%ebp), %eax

# tmp と '2' を比較する
	cmpl	$2, %eax

# この比較が成功したらラベル L3 へジャンプする
# (ラベル L3 が switch ブロックの一番目の case ブロック)
	je	.L3

# tmp と '8' を比較する
	cmpl	$8, %eax

# この比較が成功したらラベル L4 へジャンプする
# (ラベル L4 が switch ブロックの二番目の case ブロック)
	je	.L4

# ここは default ブロック
# default ケースのコード（ラベル L6） へジャンプする
	jmp	.L6

# ここが一番目の case ブロックのコード
# a = a + 1
.L3:
	addl	$1, -4(%ebp)
	jmp	.L1

# ここが二番目の case ブロックのコード
# b = b + 1
.L4:
	addl	$1, -8(%ebp)
	jmp	.L1

# ここで default ブロックのコード
# d = d + 1
.L6:
	addl	$1, -12(%ebp)

# switch-case ブロック直後のラベル
.L1:
```

``default`` を除く 各 ``case`` ブロックの最後には switch-case ブロック直後のラベルへジャンプする命令があります。
このジャンプ命令が生成される理由は、C言語のコードの ``case`` ブロックの最後に ``break`` 文を書いたからです。
もし ``break`` 文を書かなかったら、このジャンプ命令は生成されず、次の case ブロックにあるコードが実行されるようになります。
この動きは C言語の仕様に準拠したものです。

---

* [目次](/SUMMARY.md#C言語インターナル)

* [前へ](/ch05-01-translation-of-bitdddwise-operations.md#ビット演算の翻訳)

* [次へ](/ch07-01-translation-of-loop.md#ループ処理の翻訳)
