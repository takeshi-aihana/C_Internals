## 関数の返り値


関数からの返り値はレジスタを介して返すか、あるいはスタックを介して返すかのどちらかです。
基本データ型（``int``、``char``、ポインタなど）のオブジェクトが返り値の場合は全て ``eax`` レジスタに格納します。
構造体型のオブジェクトが返り値の場合はスタックに格納します。

C言語のコード：

```C
int fun(void)
{
	return 16;
}

int main(void)
{
	int a;
	a = fun();
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
	movl	$16, %eax
	popl	%ebp
	ret
	.globl	main
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	call	fun
	movl	%eax, -4(%ebp)
	movl	$0, %eax
	leave
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

# ebp レジスタの内容をスタックに退避し、その ebp レジスタに現在のスタックポインタを格納する
	pushl	%ebp
	movl	%esp, %ebp

# 戻り値 (16) を eax レジスタに移動する
	movl	$16, %eax

# ebp レジスタの内容を戻してから呼び出し戻る
#
# 注記:
# return 命令はレジスタの内容を変更することはない
# この関数の呼び出し元が eax レジスタに格納された戻り値を受け取る
	popl	%ebp
	ret

# main 関数を外部へエキスポートする
	.globl	main

# main 関数の先頭
main:

# ebp レジスタの内容をスタックに退避し、その ebp レジスタに現在のスタックポインタを格納する
	pushl	%ebp
	movl	%esp, %ebp

# ローカル変数を作成し、esp レジスタを正しく整列させる
subl	$16, %esp

# fun 関数を呼び出す
	call	fun

# fun 関数からの戻り値は eax レジスタに格納されているので
# その内容をローカル変数（スタック）に格納する
	movl	%eax, -4(%ebp)

# ここで main 関数から戻る
# 返り値は eax レジスタの中に格納される
	movl	$0, %eax
	leave
	ret
```

---

* [目次](/SUMMARY.md)

* [前へ](/ch12-01-parameter-passing.md)

* [次へ](/ch14-01-memory-allocation-for-structure.md)
