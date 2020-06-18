## 関数の呼び出し

C 言語における関数の呼び出しは ``call`` というアセンブリ言語の命令に翻訳されます。
CPU が ``call`` 命令を実行すると、次に実行する予定の命令をスタックに Push し、呼び出す関数の一番最初の命令に制御を渡します。
C 言語の ``return`` 文（C 言語の ``void`` 関数の最後にある明示的な ``return`` 文）はアセンブリ言語の ``ret`` 命令に翻訳されます。
この ``ret`` は関数を呼び出す命令とは「逆のこと」を行います。
すなわちスタックを Pop し「戻り先のアドレス」を取得して、そこへジャンプします。
そのため ``return`` 文を実行して戻り先の正しいアドレスが確実にスタックの先頭に積まれていることが重要になります。
ここで「戻り先のアドレス」をおかしくしてしまわぬよう正確なコードを生成するのはコンパイラの責任です。
では ``gcc`` コンパイラがどのようにして関数呼び出しのコードを生成するのか例を見てみることにしましょう。

C言語のコード：

```C
void fun(void)
{
	int x = 0;
	x++;
}

void main(void)
{
	fun();
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
	movl	$0, -4(%ebp)
	addl	$1, -4(%ebp)
	leave
	ret
	.globl	main
main:
	pushl	%ebp
	movl	%esp, %ebp
	call	fun
	popl	%ebp
	ret
```

生成したアセンブリ言語のコードにコメントを入れたものが、こちらです：

```asm
# ここが .text セグメントの先頭
	.text

# fun 関数を外部へエキスポートする
	.globl	fun

# fun 関数の先頭
fun:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, -4(%ebp)
	addl	$1, -4(%ebp)
	leave
	ret

# main 関数を外部へエキスポートする
	.globl	main

# main 関数の先頭
main:
	pushl	%ebp
	movl	%esp, %ebp

# main 関数が fun 関数を呼び出す
	call	fun

# main 関数から戻る → ebp レジスタを戻してから呼び出し戻る
	popl	%ebp
	ret
```

---

* [目次](/SUMMARY.md#C言語インターナル)

* [前へ](/ch10-01-function-pointer.md#関数ポインタの操作)

* [次へ](/ch12-01-parameter-passing.md#引数渡しの処理)
