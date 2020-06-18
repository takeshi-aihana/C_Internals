## 関数ポインタの操作

この C言語のコードを例にとります：

```C
// これはグローバル宣言
void fun1(void)
{
}

void main(void)
{
	void (*fptr)() = fun1;
	fptr();
}
```

これが生成したアセンブリ言語のコードです：

```asm
	movl	$fun1, 12(%esp)
	movl	12(%esp), %eax
	call	*%eax
```

スタックにおけるローカル変数の位置はそれぞれ次のとおりです（ローカル変数については[ここ](/ch03-01-stack-and-local-variables.md)で説明しました）：

```
    fptr => (ebp - 12) => -12(%ebp)
```

一時的な保管場所としてのレジスタの使い方については[ここ](/ch04-01-translation-of-arithmetic-operations.md#tempVaribaleUsage)で説明しました。

生成したアセンブリ言語のコードにコメントを入れたものが、こちらです：

```asm
# fptr = fun1
	movl	$fun1, 12(%esp)

# tmp = fptr
    movl	12(%esp), %eax

# ポインタを介して関数 tmp() を呼び出す
    call	*%eax
```

**注記：**

この例では ``ebp`` レジスタの代わりに ``esp`` レジスタを使ってローカル変数を参照しています。
スタックにのせる際に ``esp`` レジスタを使うか、または ``ebp`` レジスタを使うかは使用するコンパイラ次第です。

---

* [目次](/SUMMARY.md#C言語インターナル)

* [前へ](/ch09-01-array-indexing.md#配列の操作)

* [次へ](/ch11-01-function-call.md#関数の呼び出し)
