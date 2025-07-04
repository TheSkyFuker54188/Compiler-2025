define i32 @main()
{
L1:  
    %r1 = alloca i32
    %r1 = alloca i32
    %r3 = alloca i32
    %r1 = alloca i32
    %r0 = alloca i32
    store i32 8, ptr %r1
    store i32 12, ptr %r3
    %r2 = load i32, ptr %r1
    %r4 = load i32, ptr %r3
    %r5 = add i32 %r2,%r4
    store i32 %r5, ptr %r0
    ret i32 %r0
    store i32 8, ptr %r1
    %r1 = load i32, ptr %r0
    %r2 = load i32, ptr %r1
    %r3 = mul i32 %r1,%r2
    store i32 %r3, ptr %r0
    ret i32 %r0
    store i32 8, ptr %r1
    %r2 = load i32, ptr %r1
    %r2 = load i32, ptr %r1
    %r3 = sub i32 %r2,%r2
    %r4 = load i32, ptr %r3
    %r4 = load i32, ptr %r3
    %r5 = mul i32 %r4,%r4
    store i32 %r5, ptr %r0
    ret i32 %r0
    ret i32 %r0
}
