define i32 @main()
{
L1:  
    %r3 = alloca i32
    %r2 = alloca i32
    %r1 = alloca i32
    %r0 = alloca i32
    store i32 10, ptr %r0
    store i32 4, ptr %r1
    store i32 2, ptr %r2
    store i32 2, ptr %r3
    %r1 = load i32, ptr %r0
    %r2 = add i32 %r2,%r1
    %r5 = sub i32 %r1,%r3
    %r6 = load float, ptr %r5
    %r7 = mul i32 %r2,%r6
    ret i32 %r7
}
