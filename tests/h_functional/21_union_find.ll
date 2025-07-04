@maxN = global i32 1005
@parent = global [1005x i32] zeroinitializer
define i32 @find(i32 %r0)
{
L1:  
    ret i32 %r1
    br label %L2
    %r2 = getelementptr [1005 x i32], ptr @parent, i32 0, i32 %r1
    %r3 = call i32 @find(float %r2)
    %r2 = getelementptr [1005 x i32], ptr @parent, i32 0, i32 %r1
    store float %r3, ptr %r2
    %r2 = getelementptr [1005 x i32], ptr @parent, i32 0, i32 %r1
    ret i32 %r2
    br label %L2
L2:  
L3:  
}
define float @merge(i32 %r0,i32 %r3)
{
L1:  
    %r6 = alloca i32
    %r5 = alloca i32
    %r4 = call float @find(i32 %r3)
    store i32 %r4, ptr %r5
    %r5 = call float @find(i32 %r4)
    store i32 %r5, ptr %r6
    %r6 = load i32, ptr %r5
    %r7 = load i32, ptr %r6
    %r8 = icmp ne i32 %r6,%r7
    br i1 %r8, label %L3, label %L4
    %r7 = getelementptr [1005 x i32], ptr @parent, i32 0, i32 %r6
    store float %r5, ptr %r7
    br label %L5
L4:  
L6:  
    ret void
}
define i32 @main()
{
L1:  
    %r14 = alloca i32
    %r13 = alloca i32
    %r12 = alloca i32
    %r10 = alloca i32
    %r8 = alloca i32
    %r9 = call i32 @getint()
    store i32 %r9, ptr %r8
    %r11 = call i32 @getint()
    store i32 %r11, ptr %r10
    store i32 0, ptr %r12
    br label %L6
    %r13 = load i32, ptr %r12
    %r9 = load i32, ptr %r8
    %r10 = icmp slt i32 %r13,%r9
    br i1 %r10, label %L7, label %L8
    %r13 = getelementptr [1005 x i32], ptr @parent, i32 0, i32 %r12
    store i32 %r12, ptr %r13
    %r13 = load i32, ptr %r12
    %r16 = add i32 %r13,%r14
    store i32 %r16, ptr %r12
    br label %L7
L7:  
L8:  
L9:  
    store i32 0, ptr %r12
    br label %L9
    %r13 = load i32, ptr %r12
    %r11 = load i32, ptr %r10
    %r12 = icmp slt i32 %r13,%r11
    br i1 %r12, label %L10, label %L11
    %r13 = call i32 @getint()
    store i32 0, ptr %r13
    %r14 = call i32 @getint()
    store i32 1, ptr %r14
    %r15 = call i32 @merge(i32 %r13,i32 %r14)
    %r13 = load i32, ptr %r12
    %r16 = add i32 %r13,%r14
    store i32 %r16, ptr %r12
    br label %L10
L10:  
L11:  
L12:  
    %r13 = alloca i32
    store i32 1, ptr %r13
    store i32 0, ptr %r12
    br label %L12
    %r13 = load i32, ptr %r12
    %r9 = load i32, ptr %r8
    %r10 = icmp slt i32 %r13,%r9
    br i1 %r10, label %L13, label %L14
    %r13 = getelementptr [1005 x i32], ptr @parent, i32 0, i32 %r12
    %r14 = load i32, ptr %r13
    %r13 = load i32, ptr %r12
    %r14 = icmp eq i32 %r14,%r13
    br i1 %r14, label %L15, label %L16
    %r14 = load i32, ptr %r13
    %r17 = add i32 %r14,%r15
    store i32 %r17, ptr %r13
    br label %L17
L13:  
L14:  
L15:  
    %r14 = call i32 @putint(i32 %r13)
    ret i32 0
L16:  
L18:  
    %r13 = load i32, ptr %r12
    %r16 = add i32 %r13,%r14
    store i32 %r16, ptr %r12
    br label %L13
}
