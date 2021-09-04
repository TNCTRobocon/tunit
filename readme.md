# 使い方

* inc/tunit.hppを利用したい環境にコピーしてください。
  ヘッダーファイル単体で動作します

# 利点

SI単位系をもとに次元解析を行い、不正がないことを保証できます。
また、実行時に余計な実行時間を消費しません。

# 利用環境

* C++14がビルドできる環境

# 使用例
```c++
#include "tunit.hpp"
using namespace tunit;

int main(){

	units::ohm<float> x=3e-3;
	units::A<float> y=10;
  units::V<float> z=x*y;
	auto w=y*z*values::m;//[mW]
}

```
