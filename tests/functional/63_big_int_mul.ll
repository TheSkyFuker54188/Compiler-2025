@len = global i32 20
define i32 @main()
{
L1:  
    %r2 = load i32, ptr %r1
    %r89 = load i32, ptr %r88
    %r90 = icmp slt i32 %r2,%r89
    br i1 %r90, label %L1, label %L2
    %r2 = getelementptr [20 x i32], ptr %r6, i32 0, i32 %r1
    %r2 = getelementptr [25 x i32], ptr %r92, i32 0, i32 %r1
    store i32 %r2, ptr %r2
    %r2 = load i32, ptr %r1
    %r5 = add i32 %r2,%r3
    store i32 %r5, ptr %r1
    br label %L1
L2:  
L3:  
    store i32 0, ptr %r1
    br label %L3
    %r2 = load i32, ptr %r1
    %r91 = load i32, ptr %r90
    %r92 = icmp slt i32 %r2,%r91
    br i1 %r92, label %L4, label %L5
    %r2 = getelementptr [20 x i32], ptr %r47, i32 0, i32 %r1
    %r2 = getelementptr [25 x i32], ptr %r93, i32 0, i32 %r1
    store i32 0, ptr %r2
    %r2 = load i32, ptr %r1
    %r5 = add i32 %r2,%r3
    store i32 %r5, ptr %r1
    br label %L4
L4:  
L5:  
L6:  
    %r89 = load i32, ptr %r88
    %r91 = load i32, ptr %r90
    %r92 = add i32 %r89,%r91
    %r93 = load i32, ptr %r92
    %r95 = load i32, ptr %r94
    %r96 = sub i32 %r93,%r95
    store i32 %r96, ptr %r4
    store i32 0, ptr %r1
    br label %L6
    %r2 = load i32, ptr %r1
    %r5 = load i32, ptr %r4
    %r6 = icmp sle i32 %r2,%r5
    br i1 %r6, label %L7, label %L8
    %r2 = getelementptr [40 x i32], ptr %r94, i32 0, i32 %r1
    store i32 1, ptr %r2
    %r2 = load i32, ptr %r1
    %r5 = add i32 %r2,%r3
    store i32 0, ptr %r1
    br label %L7
L7:  
L8:  
L9:  
    store i32 0, ptr %r5
    %r91 = load i32, ptr %r90
    %r93 = load i32, ptr %r92
    %r94 = sub i32 %r91,%r93
    store i32 1, ptr %r1
    br label %L9
    %r2 = load i32, ptr %r1
    %r4 = sub i32 %r0,%r3
    %r5 = load i32, ptr %r4
    %r6 = icmp sgt i32 %r2,%r5
    br i1 %r6, label %L10, label %L11
    %r2 = getelementptr [25 x i32], ptr %r93, i32 0, i32 %r1
    store i32 0, ptr %r3
    %r89 = load i32, ptr %r88
    %r92 = sub i32 %r89,%r90
    store i32 1, ptr %r2
    br label %L12
    %r5 = sub i32 %r0,%r4
    %r7 = icmp sgt i32 %r2,%r5
    br i1 %r7, label %L13, label %L14
    %r5 = getelementptr [40 x i32], ptr %r94, i32 0, i32 %r4
    %r6 = load i32, ptr %r5
    %r3 = getelementptr [25 x i32], ptr %r92, i32 0, i32 %r2
    %r4 = load i32, ptr %r3
    %r5 = mul i32 %r3,%r4
    %r6 = load i32, ptr %r5
    %r7 = add i32 %r6,%r6
    store i32 1, ptr %r5
    %r9 = icmp sge i32 %r5,%r7
    br i1 %r9, label %L15, label %L16
    %r5 = getelementptr [40 x i32], ptr %r94, i32 0, i32 %r4
    store i32 0, ptr %r5
    %r7 = load i32, ptr %r6
    %r8 = sub i32 %r4,%r7
    %r9 = getelementptr [40 x i32], ptr %r94, i32 0, i32 %r8
    %r10 = load i32, ptr %r9
    %r9 = sdiv i32 %r5,%r7
    %r11 = add i32 %r10,%r9
    %r7 = load i32, ptr %r6
    %r8 = sub i32 %r4,%r7
    %r9 = getelementptr [40 x i32], ptr %r94, i32 0, i32 %r8
    store i32 3, ptr %r9
    br label %L17
    %r5 = getelementptr [40 x i32], ptr %r94, i32 0, i32 %r4
    store i32 0, ptr %r5
    br label %L17
L10:  
L11:  
L12:  
    %r3 = getelementptr [40 x i32], ptr %r94, i32 0, i32 %r2
    %r4 = load i32, ptr %r3
    %r7 = icmp ne i32 %r4,%r5
    br i1 %r7, label %L18, label %L19
    %r9 = getelementptr [40 x i32], ptr %r94, i32 0, i32 %r8
    %r10 = call i32 @putint(i32 %r9)
    br label %L20
L13:  
L14:  
L15:  
    %r89 = load i32, ptr %r88
    %r90 = add i32 %r4,%r89
    %r93 = load i32, ptr %r92
    %r94 = sub i32 %r90,%r93
    store i32 1, ptr %r4
    %r2 = load i32, ptr %r1
    %r5 = sub i32 %r2,%r3
    store i32 0, ptr %r1
    br label %L10
L16:  
L17:  
L18:  
    %r6 = sub i32 %r2,%r4
    store i32 1, ptr %r2
    %r7 = load i32, ptr %r6
    %r8 = sub i32 %r4,%r7
    store i32 %r8, ptr %r4
    br label %L13
L19:  
L21:  
    store i32 3, ptr %r1
    br label %L21
    %r2 = load i32, ptr %r1
    %r89 = load i32, ptr %r88
    %r92 = add i32 %r89,%r90
    %r93 = load i32, ptr %r92
    %r95 = load i32, ptr %r94
    %r96 = sub i32 %r93,%r95
    %r97 = load float, ptr %r96
    %r98 = icmp sle i32 %r2,%r97
    br i1 %r98, label %L22, label %L23
    %r2 = getelementptr [40 x i32], ptr %r94, i32 0, i32 %r1
    %r3 = call i32 @putint(i32 %r2)
    %r2 = load i32, ptr %r1
    %r5 = add i32 %r2,%r3
    store i32 0, ptr %r1
    br label %L22
L22:  
L23:  
L24:  
    ret i32 0
}
