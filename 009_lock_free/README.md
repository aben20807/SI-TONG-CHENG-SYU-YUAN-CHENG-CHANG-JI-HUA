# Compare atomic and locked version

+ Two threads , one for ++ and the other one for --.
+ Each thread do 1000000 times operations.

## Usage

```sh
$ make test
```

## Result

```
failed:
77467
real 0.09
user 0.03
sys 0.06

atomic:
0
real 0.05
user 0.03
sys 0.03

locked:
0
real 8.19
user 1.06
sys 4.46
```
