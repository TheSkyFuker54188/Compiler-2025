define i32 @exgcd(i32 %r0,i32 %r0,i32 %r2,i32 %r1)
{
L1:  
    %r5 = alloca i32
    %r1 = alloca i32
    %r8 = getelementptr [0 x i32], ptr %r2, i32 0, i32 %r7
    store float 1, ptr %r8
    %r11 = getelementptr [0 x i32], ptr %r3, i32 0, i32 %r10
    store float 0, ptr %r11
    ret i32 %r0
    br label %L2
    %r1 = load i32, ptr %r0
    %r2 = load i32, ptr %r1
    %r3 = srem i32 %r1,%r2
    %r4 = call i32 @exgcd(i32 %r1,i32 %r3,i32 %r2,i32 %r3)
    store i32 %r4, ptr %r1
    %r7 = getelementptr [0 x i32], ptr %r2, i32 0, i32 %r6
    store i32 0, ptr %r5
    %r9 = getelementptr [0 x i32], ptr %r3, i32 0, i32 %r8
    %r11 = getelementptr [0 x i32], ptr %r2, i32 0, i32 %r10
    store float 0, ptr %r11
    %r6 = load i32, ptr %r5
    %r1 = load i32, ptr %r0
    %r2 = load i32, ptr %r1
    %r3 = sdiv i32 %r1,%r2
    %r4 = load i32, ptr %r3
    %r6 = getelementptr [0 x i32], ptr %r3, i32 0, i32 %r5
    %r8 = mul i32 %r4,%r6
    %r10 = sub i32 %r6,%r8
    %r12 = getelementptr [0 x i32], ptr %r3, i32 0, i32 %r11
    store float 0, ptr %r12
    ret i32 %r1
    br label %L2
L2:  
L3:  
}
define i32 @main()
{
L1:  
    %r9 = alloca [1 x i32]
    %r6 = alloca [1 x i32]
    %r4 = alloca i32
    %r2 = alloca i32
    store i32 0, ptr %r2
    store i32 0, ptr %r4
    %r8 = getelementptr [1 x i32], ptr %r6, i32 0, i32 0
    store i32 0, ptr %r8
    %r11 = getelementptr [1 x i32], ptr %r9, i32 0, i32 0
    store i32 0, ptr %r11
    %r10 = call i32 @exgcd(i32 %r2,i32 %r4,i32 %r6,i32 %r9)
    %r12 = getelementptr [1 x i32], ptr %r6, i32 0, i32 %r11
    %r13 = load float, ptr %r12
    %r5 = load i32, ptr %r4
    %r6 = srem i32 %r13,%r5
    %r7 = load i32, ptr %r6
    %r5 = load i32, ptr %r4
    %r6 = add i32 %r7,%r5
    %r7 = load i32, ptr %r6
    %r5 = load i32, ptr %r4
    %r6 = srem i32 %r7,%r5
    %r8 = getelementptr [1 x i32], ptr %r6, i32 0, i32 %r7
    store i32 %r6, ptr %r8
    %r10 = getelementptr [1 x i32], ptr %r6, i32 0, i32 %r9
    %r11 = call i32 @putint(i32 %r10)
    ret i32 0
}
