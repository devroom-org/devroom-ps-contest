<div align="center">
    <h1>
        에디토리얼 - G번: 코드, 없는 문자
    </h1>
    <p>
        제 1회 개발자 수다방 PS 대회
    </p>
</div>

문제에서 `Trigraph`와 `ISO/IEC 646 INV`라는 말이 나왔기 때문에 이에 대해 검색한다.
[Wikipedia](https://en.wikipedia.org/wiki/ISO/IEC_646#Code_page_layout)에서 Undefined로 지정된 문자는 문제 제약 조건에서 사용할 수 없는 문자들을 포함함을 알 수 있다.

Trigraph에 대한 내용은 [ISO/IEC 9899:1999](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1256.pdf) §5.2.1.1.에서 찾을 수 있고,
아니면 [메아리 풉](https://pub.mearie.org/c%EC%9D%98%EC%9D%B4%EC%A4%91%EC%9E%90%EC%99%80%EC%82%BC%EC%A4%91%EC%9E%90)을 읽어도 좋다.

자, 배경 지식은 전부 구글링으로 획득했으니, 본격적으로 코드를 짜보아야 하는데,
조건에 의해 다음 문자를 사용할 수 없다: `#`, `\`, `^`, `[`, `]`, `|`, `{`, `}`, `~`

그렇기 때문에 우리가 직접 코드에 삼중자를 사용해야 한다! 그 이후의 풀이는 쉽다.

"Before any other processing takes place, each occurrence of one of the following sequences of three characters (called trigraph sequences) is replaced with the corresponding single character."을 수행할 때 "No other trigraph sequences exist. Each ? that does not begin one of the trigraphs listed above is not changed."인 것에 주의하여 코드를 짜면 된다.

[example_solution.cpp](./example_solution.cpp)에 예시 답안을 작성해두었다.

## 기타

테스트케이스의 대부분은 Git의 소스 코드를 바탕으로 생성되었으며, 이에 따라 Git의 라이선스 본문을 같이 포함한다.

- [LGPL-2.1](./3rd-party-licenses/LGPL-2.1)