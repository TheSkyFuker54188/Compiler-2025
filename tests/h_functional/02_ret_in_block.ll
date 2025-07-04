define i32 @main()
{
L1:  
    %r5 = alloca i32
    %r3 = alloca i32
    %r4 = alloca i32
    %r2 = alloca i32
    %r0 = alloca i32
    store i32 893, ptr %r0
    store i32 716, ptr %r2
    store i32 837, ptr %r4
    %r5 = load i32, ptr %r4
    %r8 = add i32 %r5,%r6
    store i32 %r8, ptr %r4
    %r3 = load i32, ptr %r2
    %r5 = load i32, ptr %r4
    %r6 = add i32 %r3,%r5
    store i32 128, ptr %r2
    store i32 241, ptr %r3
    %r4 = load i32, ptr %r3
    %r5 = add i32 %r4,%r4
    %r9 = sub i32 %r5,%r7
    store i32 %r9, ptr %r4
    store i32 128, ptr %r5
    %r4 = load i32, ptr %r3
    %r6 = load i32, ptr %r5
    %r7 = add i32 %r4,%r6
    %r11 = sub i32 %r7,%r9
    store i32 %r11, ptr %r3
    %r4 = load i32, ptr %r3
    %r7 = add i32 %r4,%r5
    store i32 412, ptr %r5
    %r4 = load i32, ptr %r3
    %r7 = add i32 %r4,%r5
    %r11 = sub i32 %r7,%r9
    store i32 %r11, ptr %r3
    %r4 = load i32, ptr %r3
    %r7 = sub i32 %r4,%r5
    store i32 412, ptr %r5
    %r4 = load i32, ptr %r3
    %r5 = add i32 %r5,%r4
    %r9 = srem i32 %r5,%r7
    ret i32 18
    %r4 = load i32, ptr %r3
    %r7 = add i32 %r4,%r5
    %r11 = sub i32 %r7,%r9
    store i32 %r11, ptr %r5
    %r4 = load i32, ptr %r3
    %r7 = sub i32 %r4,%r5
    %r11 = srem i32 %r7,%r9
    store i32 %r11, ptr %r3
    %r4 = load i32, ptr %r3
    %r5 = add i32 %r5,%r4
    %r9 = srem i32 %r5,%r7
    ret i32 18
    %r4 = load i32, ptr %r3
    %r5 = add i32 %r5,%r4
    %r9 = srem i32 %r5,%r7
    ret i32 18
    %r4 = load i32, ptr %r3
    %r7 = mul i32 %r4,%r5
    %r11 = srem i32 %r7,%r9
    store i32 %r11, ptr %r5
    %r4 = load i32, ptr %r3
    %r5 = add i32 %r5,%r4
    %r9 = sub i32 %r5,%r7
    store i32 18, ptr %r3
    %r4 = load i32, ptr %r3
    %r5 = add i32 %r5,%r4
    %r9 = srem i32 %r5,%r7
    ret i32 18
}
