// operation tests
print 1 + 2;
print 1 + (2 + (3 + (4 + (5 + (6 + (7 + (8 + 9)))))));
print 5 - 17;
print 3 * 5;
print 5 + 3 * 2;
print -4 + 3 * -2;

/** Multiline comments
* tests /*\/\/\/\/**
and even more
**/
print 11111111;

// basic variable tests
a = 3;
print a;
a = a + 5;
print a;
a = a / 2 + a;
print a;

/*
This is the second section.
*/
print 22222222;

// multi-variable tests
my_test1 = 144;
my_test2 = my_test1;
my_test2 = my_test2 * 2;

print my_test1;
print my_test2;

/*
This is the third section.
*/
print 33333333;

// Fibonacci sequence (while loop construction)
i = 10;
a = 0;
b = 1;
while(i) {
    print a;
    tmp = a;
    a = b;
    b = b + tmp;
    i = i - 1;
}

print 444444444;

z = 5;
if(z == 5) {
  print 1;
} else {
  print 0;
}

if(z - 1 != z + 1) {
  print 1;
} else {
  print 0;
}

print 555555555;

// Comparison test
a = 0;
while(a < 10) {
  print a;
  a = a + 1;
}

while(a > 5) {
  print a;
  a = a - 1;
}
