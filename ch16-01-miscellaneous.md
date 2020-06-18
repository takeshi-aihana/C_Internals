## その他

### 特定のセグメントの中にコードを生成する

``gcc`` コンパイラは ``.text`` セグメントの中にアセンブリ言語のコードを格納し、``.data`` または ``.bss`` セグメントの中にはグローバル変数を格納します。
``gcc`` が関数やグローバル変数といった類のコードを、どのセグメントに格納するかといったルールが予め決められています。
プログラマは、この振る舞いをオーバーライドできます。
セグメントは制御が可能です。

例を使って見てみることにしましょう。

これが C言語のコードです：

```C
void __attribute__((section ("MySegment")))
fun(void)
{
}

int main (void)
{
	fun();
	return 0;
}
```

このファイルを ``gcc`` でコンパイルして ``a.out`` ファイルを生成して下さい。
そして ``objdump`` コマンドを次のようにして ``a.out`` ファイルを調査します：


```
$ objdump -h a.out
```

このコマンドは ``a.out`` の内部にあるいろいろなセグメントの一覧を表示します。
"MySegment" と云うセグメントがあるはずです。
``__attribute__`` はグローバル変数に適用できます。

---

* [目次](/SUMMARY.md)

* [前へ](/ch15-01-mixing-c-and-assenbly.md)

* [次へ](/ch17-01-conlcusion.md)