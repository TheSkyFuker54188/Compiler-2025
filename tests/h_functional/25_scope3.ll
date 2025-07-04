define i32 @main()
{
L1:  
    %r7 = alloca i32
    %r7 = alloca i32
    %r6 = alloca i32
    %r6 = alloca i32
    %r6 = alloca i32
    %r5 = alloca i32
    %r6 = alloca i32
    %r4 = alloca i32
    %r1 = call i32 @putch(i32 %r0)
    %r3 = call i32 @putch(i32 %r2)
    store i32 1, ptr %r4
    store i32 0, ptr %r6
    %r5 = load i32, ptr %r4
    %r8 = add i32 %r5,%r6
    store i32 %r8, ptr %r4
    %r5 = load i32, ptr %r4
    %r8 = add i32 %r5,%r6
    store i32 %r8, ptr %r5
    %r6 = load i32, ptr %r5
    %r9 = add i32 %r6,%r7
    store i32 %r9, ptr %r5
    %r5 = load i32, ptr %r4
    %r6 = add i32 %r6,%r5
    %r6 = load i32, ptr %r5
    %r7 = add i32 %r6,%r6
    store i32 0, ptr %r6
    %r6 = load i32, ptr %r5
    %r9 = add i32 %r6,%r7
    store i32 %r9, ptr %r5
    %r6 = load i32, ptr %r5
    %r9 = add i32 %r6,%r7
    store i32 %r9, ptr %r6
    %r5 = load i32, ptr %r4
    %r7 = load i32, ptr %r6
    %r8 = add i32 %r5,%r7
    store i32 %r8, ptr %r4
    %r7 = load i32, ptr %r6
    %r5 = load i32, ptr %r4
    %r6 = add i32 %r7,%r5
    %r7 = load i32, ptr %r6
    %r6 = load i32, ptr %r5
    %r7 = add i32 %r7,%r6
    %r7 = load i32, ptr %r6
    %r8 = add i32 %r7,%r7
    store i32 %r8, ptr %r6
    %r6 = load i32, ptr %r5
    %r5 = load i32, ptr %r4
    %r6 = add i32 %r6,%r5
    store i32 %r6, ptr %r5
    %r7 = load i32, ptr %r6
    %r10 = add i32 %r7,%r8
    store i32 %r10, ptr %r6
    %r7 = load i32, ptr %r6
    %r10 = add i32 %r7,%r8
    store i32 %r10, ptr %r6
    %r7 = load i32, ptr %r6
    %r7 = load i32, ptr %r6
    %r8 = add i32 %r7,%r7
    %r6 = load i32, ptr %r5
    %r7 = add i32 %r8,%r6
    %r7 = load i32, ptr %r6
    %r8 = add i32 %r7,%r7
    store i32 7, ptr %r6
    %r6 = load i32, ptr %r5
    %r7 = load i32, ptr %r6
    %r8 = add i32 %r6,%r7
    store i32 7, ptr %r5
    %r7 = load i32, ptr %r6
    %r10 = add i32 %r7,%r8
    store i32 %r10, ptr %r6
    %r7 = load i32, ptr %r6
    %r10 = add i32 %r7,%r8
    store i32 %r10, ptr %r6
    store i32 7, ptr %r7
    %r7 = load i32, ptr %r6
    %r10 = add i32 %r7,%r8
    store i32 %r10, ptr %r6
    %r7 = load i32, ptr %r6
    %r8 = load i32, ptr %r7
    %r9 = add i32 %r7,%r8
    %r10 = load float, ptr %r9
    %r7 = load i32, ptr %r6
    %r8 = add i32 %r10,%r7
    %r7 = load i32, ptr %r6
    %r8 = add i32 %r8,%r7
    store i32 7, ptr %r6
    %r7 = load i32, ptr %r6
    %r7 = load i32, ptr %r6
    %r8 = add i32 %r7,%r7
    store i32 7, ptr %r6
    %r7 = load i32, ptr %r6
    %r10 = add i32 %r7,%r8
    store i32 %r10, ptr %r7
    %r8 = load i32, ptr %r7
    %r8 = load i32, ptr %r7
    %r9 = add i32 %r8,%r8
    store i32 %r9, ptr %r7
    %r7 = load i32, ptr %r6
    %r8 = load i32, ptr %r7
    %r9 = add i32 %r7,%r8
    %r10 = load float, ptr %r9
    %r7 = load i32, ptr %r6
    %r8 = add i32 %r10,%r7
    %r8 = load i32, ptr %r7
    %r9 = add i32 %r8,%r8
    store i32 %r9, ptr %r6
    %r7 = load i32, ptr %r6
    %r8 = load i32, ptr %r7
    %r9 = sub i32 %r7,%r8
    store i32 %r9, ptr %r6
    %r7 = load i32, ptr %r6
    %r7 = load i32, ptr %r6
    %r8 = sub i32 %r7,%r7
    store i32 7, ptr %r6
    %r7 = load i32, ptr %r6
    %r8 = load i32, ptr %r7
    %r9 = sub i32 %r7,%r8
    store i32 %r9, ptr %r6
    %r7 = load i32, ptr %r6
    %r10 = srem i32 %r7,%r8
    ret i32 %r10
}
