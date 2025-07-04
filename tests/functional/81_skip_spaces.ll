define i32 @main()
{
L1:  
    %r5 = call i32 @getint()
    br i1 %r5, label %L1, label %L2
    %r6 = call i32 @getint()
    %r2 = getelementptr [100 x i32], ptr %r0, i32 0, i32 %r1
    store i32 %r6, ptr %r2
    %r2 = load i32, ptr %r1
    %r5 = add i32 %r2,%r3
    store i32 %r5, ptr %r1
    br label %L1
L2:  
L3:  
    br label %L3
    br i1 %r1, label %L4, label %L5
    %r2 = load i32, ptr %r1
    %r5 = sub i32 %r2,%r3
    store i32 %r5, ptr %r1
    %r2 = getelementptr [100 x i32], ptr %r0, i32 0, i32 %r1
    %r3 = load i32, ptr %r2
    %r4 = add i32 %r3,%r3
    store i32 0, ptr %r3
    br label %L4
L4:  
L5:  
L6:  
    %r7 = srem i32 %r3,%r5
    ret i32 %r7
}
