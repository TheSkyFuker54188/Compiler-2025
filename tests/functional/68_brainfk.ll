@TAPE_LEN = global i32 65536
@BUFFER_LEN = global i32 32768
@tape = global [65536x i32] zeroinitializer
@program = global [32768x i32] zeroinitializer
@ptr11 = global i32 0
define float @read_program()
{
L1:  
    %r4 = load i32, ptr %r3
    %r6 = load i32, ptr %r5
    %r7 = icmp slt i32 %r4,%r6
    br i1 %r7, label %L1, label %L2
    %r8 = call float @getch()
    %r4 = getelementptr [32768 x i32], ptr @program, i32 0, i32 %r3
    store i32 %r8, ptr %r4
    %r4 = load i32, ptr %r3
    %r7 = add i32 %r4,%r5
    store i32 %r7, ptr %r3
    br label %L1
L2:  
L3:  
    %r4 = getelementptr [32768 x i32], ptr @program, i32 0, i32 %r3
    store i32 0, ptr %r4
}
define float @interpret(i32 %r0)
{
L1:  
    %r8 = alloca i32
    %r7 = alloca i32
    %r6 = alloca i32
    store i32 0, ptr %r8
    br label %L3
    %r9 = getelementptr [0 x i32], ptr %r5, i32 0, i32 %r8
    br i1 %r9, label %L4, label %L5
    %r9 = getelementptr [0 x i32], ptr %r5, i32 0, i32 %r8
    store i32 0, ptr %r6
    %r7 = load i32, ptr %r6
    %r10 = icmp eq i32 %r7,%r8
    br i1 %r10, label %L6, label %L7
    %r11 = load i32, ptr @ptr11
    %r12 = load i32, ptr %r11
    %r15 = add i32 %r12,%r13
    %r16 = load i32, ptr @ptr11
    store i32 %r15, ptr %r16
    br label %L8
    %r7 = load i32, ptr %r6
    %r10 = icmp eq i32 %r7,%r8
    br i1 %r10, label %L9, label %L10
    %r11 = load i32, ptr @ptr11
    %r12 = load i32, ptr %r11
    %r15 = sub i32 %r12,%r13
    %r16 = load i32, ptr @ptr11
    store i32 %r15, ptr %r16
    br label %L11
    %r7 = load i32, ptr %r6
    %r10 = icmp eq i32 %r7,%r8
    br i1 %r10, label %L12, label %L13
    %r11 = load i32, ptr @ptr11
    %r12 = getelementptr [65536 x i32], ptr @tape, i32 0, i32 %r11
    %r13 = load float, ptr %r12
    %r16 = add i32 %r13,%r14
    %r17 = load i32, ptr @ptr11
    %r18 = getelementptr [65536 x i32], ptr @tape, i32 0, i32 %r17
    store float %r16, ptr %r18
    br label %L14
    %r7 = load i32, ptr %r6
    %r10 = icmp eq i32 %r7,%r8
    br i1 %r10, label %L15, label %L16
    %r11 = load i32, ptr @ptr11
    %r12 = getelementptr [65536 x i32], ptr @tape, i32 0, i32 %r11
    %r13 = load float, ptr %r12
    %r16 = sub i32 %r13,%r14
    %r17 = load i32, ptr @ptr11
    %r18 = getelementptr [65536 x i32], ptr @tape, i32 0, i32 %r17
    store float %r16, ptr %r18
    br label %L17
    %r7 = load i32, ptr %r6
    %r10 = icmp eq i32 %r7,%r8
    br i1 %r10, label %L18, label %L19
    %r11 = load i32, ptr @ptr11
    %r12 = getelementptr [65536 x i32], ptr @tape, i32 0, i32 %r11
    %r13 = call float @putch(float %r12)
    br label %L20
    %r7 = load i32, ptr %r6
    %r10 = icmp eq i32 %r7,%r8
    br i1 %r10, label %L21, label %L22
    %r11 = call float @getch()
    %r12 = load i32, ptr @ptr11
    %r13 = getelementptr [65536 x i32], ptr @tape, i32 0, i32 %r12
    store i32 %r11, ptr %r13
    br label %L23
    %r7 = load i32, ptr %r6
    %r10 = icmp eq i32 %r7,%r8
    %r11 = load float, ptr %r10
    %r12 = load i32, ptr @ptr11
    %r13 = getelementptr [65536 x i32], ptr @tape, i32 0, i32 %r12
    %r14 = load i32, ptr %r13
    %r15 = and i32 %r11,%r14
    br i1 %r15, label %L24, label %L25
    store i32 1, ptr %r7
    br label %L27
    %r8 = load i32, ptr %r7
    %r11 = icmp sgt i32 %r8,%r9
    br i1 %r11, label %L28, label %L29
    %r12 = sub i32 %r8,%r10
    store i32 %r12, ptr %r8
    %r9 = getelementptr [0 x i32], ptr %r5, i32 0, i32 %r8
    store i32 0, ptr %r6
    %r7 = load i32, ptr %r6
    %r10 = icmp eq i32 %r7,%r8
    br i1 %r10, label %L30, label %L31
    %r8 = load i32, ptr %r7
    %r11 = sub i32 %r8,%r9
    store i32 %r11, ptr %r7
    br label %L32
    %r7 = load i32, ptr %r6
    %r10 = icmp eq i32 %r7,%r8
    br i1 %r10, label %L33, label %L34
    %r8 = load i32, ptr %r7
    %r11 = add i32 %r8,%r9
    store i32 %r11, ptr %r7
    br label %L35
L4:  
L5:  
L6:  
L7:  
L8:  
L9:  
    %r12 = add i32 %r8,%r10
    store i32 %r12, ptr %r8
    br label %L4
L10:  
L11:  
L12:  
    br label %L8
L13:  
L14:  
L15:  
    br label %L11
L16:  
L17:  
L18:  
    br label %L14
L19:  
L20:  
L21:  
    br label %L17
L22:  
L23:  
L24:  
    br label %L20
L25:  
L27:  
    br label %L23
L28:  
L29:  
L30:  
    br label %L26
L31:  
L32:  
L33:  
    br label %L28
L34:  
L36:  
    br label %L32
}
define i32 @main()
{
L1:  
    %r9 = call i32 @read_program()
    %r10 = load i32, ptr @program
    %r11 = call i32 @interpret(i32 %r10)
    ret i32 0
}
