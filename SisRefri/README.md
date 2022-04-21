
### [Problem Statement](https://docs.google.com/spreadsheets/d/1NBjuOgz4UKXTvdi8rWU8ktnI30kscC70W1K5dwVMzrM/edit#gid=0)

| HI-TEMP | B1-MAN | B2-ALTA | B3-SOBRE | LED-MAN | LED-AUTO |
| :--: | :--: | :--: | :--: | :--: | :--: |
| 0 | 0 | 0 | 0 | 0 | 0 |
| 0 | 0 | 0 | 1 | 0 | 1 |
| 0 | 0 | 1 | 0 | 0 | 1 |
| 0 | 0 | 1 | 1 | 0 | 1 |
| 0 | 1 | 0 | 0 | 1 | 0 |
| 0 | 1 | 0 | 1 | 1 | 1 |
| 0 | 1 | 1 | 0 | 1 | 1 |
| 0 | 1 | 1 | 1 | 1 | 1 |
| 1 | 0 | 0 | 0 | 0 | 1 |
| 1 | 0 | 0 | 1 | 1 | 1 |
| 1 | 0 | 1 | 0 | 1 | 1 |
| 1 | 0 | 1 | 1 | 1 | 1 |
| 1 | 1 | 0 | 0 | 1 | 1 |
| 1 | 1 | 0 | 1 | 1 | 1 |
| 1 | 1 | 1 | 0 | 1 | 1 |
| 1 | 1 | 1 | 1 | 1 | 1 |

-----

## Online minimization of boolean functions tool

### [Truth table](http://tma.main.jp/logic/logic.php?lang=en&type=4&v0=a&v1=b&v2=c&v3=d&00=0&01=0&02=0&03=0&04=1&05=1&06=1&07=1&08=0&09=1&0a=1&0b=1&0c=1&0d=1&0e=1&0f=1)

| a | b | c | d | Output |
| :--: | :--: | :--: | :--: | :--: |
| 0 | 0 | 0 | 0 | 0 |
| 0 | 0 | 0 | 1 | 0 |
| 0 | 0 | 1 | 0 | 0 |
| 0 | 0 | 1 | 1 | 0 |
| 0 | 1 | 0 | 0 | 1 |
| 0 | 1 | 0 | 1 | 1 |
| 0 | 1 | 1 | 0 | 1 |
| 0 | 1 | 1 | 1 | 1 |
| 1 | 0 | 0 | 0 | 0 |
| 1 | 0 | 0 | 1 | 1 |
| 1 | 0 | 1 | 0 | 1 |
| 1 | 0 | 1 | 1 | 1 |
| 1 | 1 | 0 | 0 | 1 |
| 1 | 1 | 0 | 1 | 1 |
| 1 | 1 | 1 | 0 | 1 |
| 1 | 1 | 1 | 1 | 1 |

```
DNF = ~ab~c~d + ~ab~cd + ~abc~d + ~abcd + a~b~cd + a~bc~d + a~bcd + ab~c~d + ab~cd + abc~d + abcd

CNF = (a + b + c + d) (a + b + c + ~d) (a + b + ~c + d) (a + b + ~c + ~d) (~a + b + c + d)

Minimal Form = ad + ac + b
```

————

### [Truth table](http://tma.main.jp/logic/logic.php?lang=en&type=4&v0=a&v1=b&v2=c&v3=d&00=0&01=1&02=1&03=1&04=0&05=1&06=1&07=1&08=1&09=1&0a=1&0b=1&0c=1&0d=1&0e=1&0f=1)

| a | b | c | d | Output |
| :--: | :--: | :--: | :--: | :--: |
| 0 | 0 | 0 | 0 | 0 |
| 0 | 0 | 0 | 1 | 1 |
| 0 | 0 | 1 | 0 | 1 |
| 0 | 0 | 1 | 1 | 1 |
| 0 | 1 | 0 | 0 | 0 |
| 0 | 1 | 0 | 1 | 1 |
| 0 | 1 | 1 | 0 | 1 |
| 0 | 1 | 1 | 1 | 1 |
| 1 | 0 | 0 | 0 | 1 |
| 1 | 0 | 0 | 1 | 1 |
| 1 | 0 | 1 | 0 | 1 |
| 1 | 0 | 1 | 1 | 1 |
| 1 | 1 | 0 | 0 | 1 |
| 1 | 1 | 0 | 1 | 1 |
| 1 | 1 | 1 | 0 | 1 |
| 1 | 1 | 1 | 1 | 1 |

```
DNF = ~a~b~cd + ~a~bc~d + ~a~bcd + ~ab~cd + ~abc~d + ~abcd + a~b~c~d + a~b~cd + a~bc~d + a~bcd + ab~c~d + ab~cd + abc~d + abcd

CNF = (a + b + c + d) (a + ~b + c + d)

Minimal Form = a + c + d
```
