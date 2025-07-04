@SHIFT_TABLE = global [16 x i32] [i32 1,i32 2,i32 4,i32 8,i32 16,i32 32,i32 64,i32 128,i32 256,i32 512,i32 1024,i32 2048,i32 4096,i32 8192,i32 16384,i32 32768]
define i32 @long_func()
{
L1:  
    %r24 = load i32, ptr %r23
    %r27 = icmp sgt i32 %r24,%r25
    br i1 %r27, label %L1, label %L2
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    store i32 %r23, ptr %r18
    store i32 1, ptr %r19
    br label %L3
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L4, label %L5
    %r19 = load i32, ptr %r18
    %r22 = srem i32 %r19,%r20
    %r23 = srem i32 %r19,%r21
    %r24 = load i32, ptr %r23
    %r25 = and i32 %r22,%r24
    br i1 %r25, label %L6, label %L7
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 2, ptr %r16
    br label %L8
L2:  
L3:  
    %r24 = alloca i32
    %r22 = alloca i32
    %r20 = alloca i32
    store i32 0, ptr %r16
    %r17 = call i32 @putint(i32 %r16)
    %r19 = call i32 @putch(i32 %r18)
    store i32 2, ptr %r20
    store i32 65535, ptr %r22
    store i32 0, ptr %r24
    br label %L192
    %r23 = load i32, ptr %r22
    %r26 = icmp sgt i32 %r23,%r24
    br i1 %r26, label %L193, label %L194
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    store i32 %r22, ptr %r18
    store i32 1, ptr %r19
    br label %L195
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L196, label %L197
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r23,%r23
    br i1 %r25, label %L198, label %L199
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L200
L4:  
L5:  
L6:  
    %r22 = alloca i32
    %r26 = alloca i32
    %r17 = alloca i32
    br i1 %r16, label %L9, label %L10
    store i32 0, ptr %r17
    store i32 2, ptr %r26
    store i32 0, ptr %r22
    br label %L12
    br i1 %r26, label %L13, label %L14
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    store i32 %r26, ptr %r18
    store i32 1, ptr %r19
    br label %L15
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L16, label %L17
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r23,%r23
    br i1 %r25, label %L18, label %L19
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L20
L7:  
L9:  
    %r22 = sdiv i32 %r18,%r20
    store i32 2, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 %r23, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L4
L10:  
L12:  
    %r22 = alloca i32
    %r22 = alloca i32
    %r26 = alloca i32
    store i32 2, ptr %r26
    store i32 2, ptr %r22
    store i32 65535, ptr %r22
    br label %L96
    br i1 %r22, label %L97, label %L98
    store i32 65535, ptr %r16
    store i32 0, ptr %r17
    store i32 %r22, ptr %r18
    store i32 1, ptr %r19
    br label %L99
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L100, label %L101
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r23,%r23
    br i1 %r25, label %L102, label %L103
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L104
L13:  
L14:  
L15:  
    store i32 %r22, ptr %r16
    store i32 %r16, ptr %r25
    br label %L11
L16:  
L17:  
L18:  
    %r18 = alloca i32
    %r23 = alloca i32
    %r17 = alloca i32
    br i1 %r16, label %L21, label %L22
    store i32 %r22, ptr %r17
    store i32 %r17, ptr %r23
    br label %L24
    br i1 %r23, label %L25, label %L26
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    store i32 0, ptr %r18
    store i32 %r23, ptr %r19
    br label %L27
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L28, label %L29
    %r19 = load i32, ptr %r18
    %r22 = srem i32 %r19,%r20
    br i1 %r22, label %L30, label %L31
    %r23 = srem i32 %r19,%r21
    %r24 = load i32, ptr %r23
    %r27 = icmp eq i32 %r24,%r25
    br i1 %r27, label %L33, label %L34
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L35
L19:  
L21:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 0, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L16
L22:  
L24:  
    %r18 = alloca i32
    %r18 = alloca i32
    %r23 = alloca i32
    store i32 0, ptr %r23
    store i32 0, ptr %r18
    br label %L54
    br i1 %r18, label %L55, label %L56
    store i32 1, ptr %r16
    store i32 0, ptr %r17
    store i32 %r23, ptr %r18
    store i32 %r18, ptr %r19
    br label %L57
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L58, label %L59
    %r19 = load i32, ptr %r18
    %r22 = srem i32 %r19,%r20
    br i1 %r22, label %L60, label %L61
    %r23 = srem i32 %r19,%r21
    %r24 = load i32, ptr %r23
    %r27 = icmp eq i32 %r24,%r25
    br i1 %r27, label %L63, label %L64
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L65
L25:  
L26:  
L27:  
    store i32 0, ptr %r16
    store i32 %r16, ptr %r22
    br label %L23
L28:  
L29:  
L30:  
    store i32 %r16, ptr %r18
    store i32 1, ptr %r16
    store i32 0, ptr %r17
    store i32 0, ptr %r18
    store i32 %r23, ptr %r19
    br label %L39
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L40, label %L41
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r24 = load i32, ptr %r23
    %r25 = and i32 %r23,%r24
    br i1 %r25, label %L42, label %L43
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L44
L31:  
L32:  
L33:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 %r23, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L28
L34:  
L36:  
    br label %L32
    %r23 = srem i32 %r19,%r21
    br i1 %r23, label %L36, label %L37
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L38
L37:  
L39:  
    br label %L32
L40:  
L41:  
L42:  
    store i32 %r16, ptr %r23
    %r28 = icmp sgt i32 %r24,%r26
    br i1 %r28, label %L45, label %L46
    store i32 0, ptr %r16
    br label %L47
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    %r24 = load i32, ptr %r23
    %r26 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r25
    %r27 = load i32, ptr %r26
    %r28 = mul i32 %r24,%r27
    store i32 0, ptr %r18
    store i32 1, ptr %r19
    br label %L48
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L49, label %L50
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r24 = load i32, ptr %r23
    %r25 = and i32 %r23,%r24
    br i1 %r25, label %L51, label %L52
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L53
L43:  
L45:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 %r23, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L40
L46:  
L47:  
L48:  
    store i32 %r16, ptr %r23
    store i32 1, ptr %r17
    br label %L25
L49:  
L50:  
L51:  
    br label %L47
L52:  
L54:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 %r23, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L49
L55:  
L56:  
L57:  
    store i32 %r23, ptr %r16
    store i32 %r16, ptr %r17
    store i32 15, ptr %r18
    store i32 1, ptr %r19
    %r23 = icmp sge i32 %r19,%r21
    br i1 %r23, label %L84, label %L85
    %r22 = icmp slt i32 %r18,%r20
    br i1 %r22, label %L87, label %L88
    store i32 65535, ptr %r16
    br label %L89
    store i32 0, ptr %r16
    br label %L89
L58:  
L59:  
L60:  
    store i32 %r16, ptr %r18
    store i32 1, ptr %r16
    store i32 0, ptr %r17
    store i32 %r23, ptr %r18
    store i32 1, ptr %r19
    br label %L69
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L70, label %L71
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r24 = load i32, ptr %r23
    %r25 = and i32 %r23,%r24
    br i1 %r25, label %L72, label %L73
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L74
L61:  
L62:  
L63:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 %r23, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L58
L64:  
L66:  
    br label %L62
    %r23 = srem i32 %r19,%r21
    br i1 %r23, label %L66, label %L67
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L68
L67:  
L69:  
    br label %L62
L70:  
L71:  
L72:  
    store i32 %r16, ptr %r18
    %r23 = icmp sgt i32 %r19,%r21
    br i1 %r23, label %L75, label %L76
    store i32 0, ptr %r16
    br label %L77
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    %r21 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r20
    %r22 = load i32, ptr %r21
    %r23 = mul i32 %r18,%r22
    store i32 %r23, ptr %r18
    store i32 1, ptr %r19
    br label %L78
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L79, label %L80
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r24 = load i32, ptr %r23
    %r25 = and i32 %r23,%r24
    br i1 %r25, label %L81, label %L82
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L83
L73:  
L75:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 %r23, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L70
L76:  
L77:  
L78:  
    store i32 %r16, ptr %r18
    store i32 1, ptr %r23
    br label %L55
L79:  
L80:  
L81:  
    br label %L77
L82:  
L84:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 %r23, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L79
L85:  
L86:  
L87:  
    store i32 %r16, ptr %r26
    br label %L13
L88:  
L89:  
L90:  
    br label %L86
    %r23 = icmp sgt i32 %r19,%r21
    br i1 %r23, label %L90, label %L91
    %r22 = icmp sgt i32 %r18,%r20
    br i1 %r22, label %L93, label %L94
    %r20 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r19
    %r21 = load i32, ptr %r20
    %r22 = sdiv i32 %r18,%r21
    store i32 %r22, ptr %r18
    %r22 = add i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r21 = sub i32 %r24,%r19
    %r25 = add i32 %r21,%r23
    %r26 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r25
    %r27 = load i32, ptr %r26
    %r28 = sub i32 %r23,%r27
    store i32 0, ptr %r16
    br label %L95
    %r20 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r19
    %r21 = load i32, ptr %r20
    %r22 = sdiv i32 %r18,%r21
    store i32 %r22, ptr %r16
    br label %L95
L91:  
L92:  
L93:  
    br label %L86
L94:  
L95:  
L96:  
    br label %L92
    store i32 1, ptr %r16
    br label %L92
L97:  
L98:  
L99:  
    store i32 %r22, ptr %r16
    store i32 %r16, ptr %r21
    store i32 65535, ptr %r18
    store i32 1, ptr %r19
    %r23 = icmp sge i32 %r19,%r21
    br i1 %r23, label %L180, label %L181
    %r22 = icmp slt i32 %r18,%r20
    br i1 %r22, label %L183, label %L184
    store i32 65535, ptr %r16
    br label %L185
    store i32 0, ptr %r16
    br label %L185
L100:  
L101:  
L102:  
    %r27 = alloca i32
    %r23 = alloca i32
    %r17 = alloca i32
    br i1 %r16, label %L105, label %L106
    store i32 %r22, ptr %r17
    store i32 %r26, ptr %r23
    br label %L108
    br i1 %r23, label %L109, label %L110
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    store i32 0, ptr %r18
    store i32 %r23, ptr %r19
    br label %L111
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L112, label %L113
    %r22 = srem i32 %r18,%r20
    br i1 %r22, label %L114, label %L115
    %r23 = srem i32 %r19,%r21
    %r24 = load i32, ptr %r23
    %r27 = icmp eq i32 %r24,%r25
    br i1 %r27, label %L117, label %L118
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L119
L103:  
L105:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L100
L106:  
L108:  
    %r27 = alloca i32
    %r27 = alloca i32
    %r23 = alloca i32
    store i32 15, ptr %r23
    store i32 15, ptr %r27
    br label %L138
    br i1 %r27, label %L139, label %L140
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    store i32 %r23, ptr %r18
    store i32 %r27, ptr %r19
    br label %L141
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L142, label %L143
    %r22 = srem i32 %r18,%r20
    br i1 %r22, label %L144, label %L145
    %r23 = srem i32 %r19,%r21
    %r24 = load i32, ptr %r23
    %r27 = icmp eq i32 %r24,%r25
    br i1 %r27, label %L147, label %L148
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L149
L109:  
L110:  
L111:  
    store i32 0, ptr %r16
    store i32 %r16, ptr %r22
    br label %L107
L112:  
L113:  
L114:  
    store i32 %r16, ptr %r27
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    store i32 0, ptr %r18
    store i32 %r23, ptr %r19
    br label %L123
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L124, label %L125
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r24 = load i32, ptr %r23
    %r25 = and i32 %r23,%r24
    br i1 %r25, label %L126, label %L127
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L128
L115:  
L116:  
L117:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 %r23, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L112
L118:  
L120:  
    br label %L116
    %r23 = srem i32 %r19,%r21
    br i1 %r23, label %L120, label %L121
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L122
L121:  
L123:  
    br label %L116
L124:  
L125:  
L126:  
    store i32 %r16, ptr %r23
    %r28 = icmp sgt i32 %r24,%r26
    br i1 %r28, label %L129, label %L130
    store i32 0, ptr %r16
    br label %L131
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    %r24 = load i32, ptr %r23
    %r26 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r25
    %r27 = load i32, ptr %r26
    %r28 = mul i32 %r24,%r27
    store i32 0, ptr %r18
    store i32 1, ptr %r19
    br label %L132
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L133, label %L134
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r24 = load i32, ptr %r23
    %r25 = and i32 %r23,%r24
    br i1 %r25, label %L135, label %L136
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L137
L127:  
L129:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 %r23, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L124
L130:  
L131:  
L132:  
    store i32 %r16, ptr %r23
    store i32 %r27, ptr %r17
    br label %L109
L133:  
L134:  
L135:  
    br label %L131
L136:  
L138:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 %r23, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L133
L139:  
L140:  
L141:  
    store i32 %r23, ptr %r16
    store i32 %r16, ptr %r26
    store i32 %r22, ptr %r18
    store i32 1, ptr %r19
    %r23 = icmp sge i32 %r19,%r21
    br i1 %r23, label %L168, label %L169
    %r22 = icmp slt i32 %r18,%r20
    br i1 %r22, label %L171, label %L172
    store i32 65535, ptr %r16
    br label %L173
    store i32 0, ptr %r16
    br label %L173
L142:  
L143:  
L144:  
    store i32 %r16, ptr %r27
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    store i32 %r23, ptr %r18
    store i32 %r27, ptr %r19
    br label %L153
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L154, label %L155
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r24 = load i32, ptr %r23
    %r25 = and i32 %r23,%r24
    br i1 %r25, label %L156, label %L157
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L158
L145:  
L146:  
L147:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 %r23, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L142
L148:  
L150:  
    br label %L146
    %r23 = srem i32 %r19,%r21
    br i1 %r23, label %L150, label %L151
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L152
L151:  
L153:  
    br label %L146
L154:  
L155:  
L156:  
    store i32 %r16, ptr %r27
    %r32 = icmp sgt i32 %r28,%r30
    br i1 %r32, label %L159, label %L160
    store i32 0, ptr %r16
    br label %L161
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    %r28 = load i32, ptr %r27
    %r30 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r29
    %r31 = load i32, ptr %r30
    %r32 = mul i32 %r28,%r31
    store i32 %r32, ptr %r18
    store i32 1, ptr %r19
    br label %L162
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L163, label %L164
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r24 = load i32, ptr %r23
    %r25 = and i32 %r23,%r24
    br i1 %r25, label %L165, label %L166
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L167
L157:  
L159:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 %r23, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L154
L160:  
L161:  
L162:  
    store i32 %r16, ptr %r27
    store i32 %r27, ptr %r23
    br label %L139
L163:  
L164:  
L165:  
    br label %L161
L166:  
L168:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 %r23, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L163
L169:  
L170:  
L171:  
    store i32 %r16, ptr %r22
    br label %L97
L172:  
L173:  
L174:  
    br label %L170
    %r23 = icmp sgt i32 %r19,%r21
    br i1 %r23, label %L174, label %L175
    %r22 = icmp sgt i32 %r18,%r20
    br i1 %r22, label %L177, label %L178
    %r20 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r19
    %r21 = load i32, ptr %r20
    %r22 = sdiv i32 %r18,%r21
    store i32 %r22, ptr %r18
    %r22 = add i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r21 = sub i32 %r24,%r19
    %r25 = add i32 %r21,%r23
    %r26 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r25
    %r27 = load i32, ptr %r26
    %r28 = sub i32 %r23,%r27
    store i32 0, ptr %r16
    br label %L179
    %r20 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r19
    %r21 = load i32, ptr %r20
    %r22 = sdiv i32 %r18,%r21
    store i32 %r22, ptr %r16
    br label %L179
L175:  
L176:  
L177:  
    br label %L170
L178:  
L179:  
L180:  
    br label %L176
    store i32 1, ptr %r16
    br label %L176
L181:  
L182:  
L183:  
    store i32 %r16, ptr %r23
    br label %L1
L184:  
L185:  
L186:  
    br label %L182
    %r23 = icmp sgt i32 %r19,%r21
    br i1 %r23, label %L186, label %L187
    %r22 = icmp sgt i32 %r18,%r20
    br i1 %r22, label %L189, label %L190
    %r20 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r19
    %r21 = load i32, ptr %r20
    %r22 = sdiv i32 %r18,%r21
    store i32 %r22, ptr %r18
    %r22 = add i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r21 = sub i32 %r24,%r19
    %r25 = add i32 %r21,%r23
    %r26 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r25
    %r27 = load i32, ptr %r26
    %r28 = sub i32 %r23,%r27
    store i32 0, ptr %r16
    br label %L191
    %r20 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r19
    %r21 = load i32, ptr %r20
    %r22 = sdiv i32 %r18,%r21
    store i32 %r22, ptr %r16
    br label %L191
L187:  
L188:  
L189:  
    br label %L182
L190:  
L191:  
L192:  
    br label %L188
    store i32 1, ptr %r16
    br label %L188
L193:  
L194:  
L195:  
    %r21 = alloca i32
    %r27 = alloca i32
    %r25 = alloca i32
    store i32 0, ptr %r16
    %r17 = call i32 @putint(i32 %r16)
    %r19 = call i32 @putch(i32 %r18)
    store i32 2, ptr %r20
    br label %L384
    %r24 = icmp slt i32 %r20,%r22
    br i1 %r24, label %L385, label %L386
    store i32 2, ptr %r25
    store i32 2, ptr %r27
    store i32 16, ptr %r21
    br label %L387
    %r28 = load i32, ptr %r27
    %r31 = icmp sgt i32 %r28,%r29
    br i1 %r31, label %L388, label %L389
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    store i32 %r27, ptr %r18
    store i32 1, ptr %r19
    br label %L390
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L391, label %L392
    %r22 = srem i32 %r18,%r20
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r22,%r23
    br i1 %r25, label %L393, label %L394
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 16, ptr %r16
    br label %L395
L196:  
L197:  
L198:  
    %r21 = alloca i32
    %r25 = alloca i32
    %r17 = alloca i32
    br i1 %r16, label %L201, label %L202
    store i32 0, ptr %r17
    store i32 2, ptr %r25
    store i32 0, ptr %r21
    br label %L204
    br i1 %r25, label %L205, label %L206
    store i32 15, ptr %r16
    store i32 0, ptr %r17
    store i32 %r25, ptr %r18
    store i32 1, ptr %r19
    br label %L207
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L208, label %L209
    %r22 = srem i32 %r18,%r20
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r22,%r23
    br i1 %r25, label %L210, label %L211
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 0, ptr %r16
    br label %L212
L199:  
L201:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L196
L202:  
L204:  
    %r21 = alloca i32
    %r21 = alloca i32
    %r25 = alloca i32
    store i32 2, ptr %r25
    store i32 2, ptr %r21
    store i32 0, ptr %r21
    br label %L288
    br i1 %r21, label %L289, label %L290
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    store i32 %r21, ptr %r18
    store i32 1, ptr %r19
    br label %L291
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L292, label %L293
    %r22 = srem i32 %r18,%r20
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r22,%r23
    br i1 %r25, label %L294, label %L295
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 0, ptr %r16
    br label %L296
L205:  
L206:  
L207:  
    store i32 2, ptr %r16
    store i32 %r16, ptr %r24
    br label %L203
L208:  
L209:  
L210:  
    %r18 = alloca i32
    %r22 = alloca i32
    %r17 = alloca i32
    br i1 %r16, label %L213, label %L214
    store i32 2, ptr %r17
    store i32 %r17, ptr %r22
    br label %L216
    br i1 %r22, label %L217, label %L218
    store i32 65535, ptr %r16
    store i32 0, ptr %r17
    store i32 0, ptr %r18
    store i32 %r22, ptr %r19
    br label %L219
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L220, label %L221
    %r19 = load i32, ptr %r18
    %r22 = srem i32 %r19,%r20
    br i1 %r22, label %L222, label %L223
    %r23 = srem i32 %r19,%r21
    %r27 = icmp eq i32 %r23,%r25
    br i1 %r27, label %L225, label %L226
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L227
L211:  
L213:  
    %r22 = sdiv i32 %r18,%r20
    store i32 0, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L208
L214:  
L216:  
    %r18 = alloca i32
    %r18 = alloca i32
    %r22 = alloca i32
    store i32 0, ptr %r22
    store i32 0, ptr %r18
    br label %L246
    br i1 %r18, label %L247, label %L248
    store i32 1, ptr %r16
    store i32 0, ptr %r17
    store i32 %r22, ptr %r18
    store i32 %r18, ptr %r19
    br label %L249
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L250, label %L251
    %r19 = load i32, ptr %r18
    %r22 = srem i32 %r19,%r20
    br i1 %r22, label %L252, label %L253
    %r23 = srem i32 %r19,%r21
    %r27 = icmp eq i32 %r23,%r25
    br i1 %r27, label %L255, label %L256
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L257
L217:  
L218:  
L219:  
    store i32 0, ptr %r16
    store i32 %r16, ptr %r21
    br label %L215
L220:  
L221:  
L222:  
    store i32 %r16, ptr %r18
    store i32 1, ptr %r16
    store i32 0, ptr %r17
    store i32 0, ptr %r18
    store i32 %r22, ptr %r19
    br label %L231
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L232, label %L233
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r23,%r23
    br i1 %r25, label %L234, label %L235
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L236
L223:  
L224:  
L225:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L220
L226:  
L228:  
    br label %L224
    %r23 = srem i32 %r19,%r21
    br i1 %r23, label %L228, label %L229
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L230
L229:  
L231:  
    br label %L224
L232:  
L233:  
L234:  
    store i32 %r16, ptr %r22
    %r27 = icmp sgt i32 %r23,%r25
    br i1 %r27, label %L237, label %L238
    store i32 0, ptr %r16
    br label %L239
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    %r23 = load i32, ptr %r22
    %r25 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r24
    %r26 = load i32, ptr %r25
    %r27 = mul i32 %r23,%r26
    store i32 0, ptr %r18
    store i32 1, ptr %r19
    br label %L240
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L241, label %L242
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r23,%r23
    br i1 %r25, label %L243, label %L244
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L245
L235:  
L237:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L232
L238:  
L239:  
L240:  
    store i32 %r16, ptr %r22
    store i32 1, ptr %r17
    br label %L217
L241:  
L242:  
L243:  
    br label %L239
L244:  
L246:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L241
L247:  
L248:  
L249:  
    store i32 %r22, ptr %r16
    store i32 %r16, ptr %r17
    store i32 0, ptr %r18
    store i32 1, ptr %r19
    %r23 = icmp sge i32 %r19,%r21
    br i1 %r23, label %L276, label %L277
    %r22 = icmp slt i32 %r18,%r20
    br i1 %r22, label %L279, label %L280
    store i32 65535, ptr %r16
    br label %L281
    store i32 0, ptr %r16
    br label %L281
L250:  
L251:  
L252:  
    store i32 %r16, ptr %r18
    store i32 1, ptr %r16
    store i32 0, ptr %r17
    store i32 %r22, ptr %r18
    store i32 1, ptr %r19
    br label %L261
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L262, label %L263
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r23,%r23
    br i1 %r25, label %L264, label %L265
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L266
L253:  
L254:  
L255:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L250
L256:  
L258:  
    br label %L254
    %r23 = srem i32 %r19,%r21
    br i1 %r23, label %L258, label %L259
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L260
L259:  
L261:  
    br label %L254
L262:  
L263:  
L264:  
    store i32 %r16, ptr %r18
    %r23 = icmp sgt i32 %r19,%r21
    br i1 %r23, label %L267, label %L268
    store i32 0, ptr %r16
    br label %L269
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    %r21 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r20
    %r22 = load i32, ptr %r21
    %r23 = mul i32 %r18,%r22
    store i32 65535, ptr %r18
    store i32 1, ptr %r19
    br label %L270
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L271, label %L272
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r23,%r23
    br i1 %r25, label %L273, label %L274
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L275
L265:  
L267:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L262
L268:  
L269:  
L270:  
    store i32 %r16, ptr %r18
    store i32 1, ptr %r22
    br label %L247
L271:  
L272:  
L273:  
    br label %L269
L274:  
L276:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L271
L277:  
L278:  
L279:  
    store i32 %r16, ptr %r25
    br label %L205
L280:  
L281:  
L282:  
    br label %L278
    %r23 = icmp sgt i32 %r19,%r21
    br i1 %r23, label %L282, label %L283
    %r22 = icmp sgt i32 %r18,%r20
    br i1 %r22, label %L285, label %L286
    %r20 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r19
    %r21 = load i32, ptr %r20
    %r22 = sdiv i32 %r18,%r21
    store i32 %r22, ptr %r18
    %r22 = add i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r21 = sub i32 %r24,%r19
    %r25 = add i32 %r21,%r23
    %r26 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r25
    %r27 = load i32, ptr %r26
    %r28 = sub i32 %r23,%r27
    store i32 0, ptr %r16
    br label %L287
    %r20 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r19
    %r21 = load i32, ptr %r20
    %r22 = sdiv i32 %r18,%r21
    store i32 %r22, ptr %r16
    br label %L287
L283:  
L284:  
L285:  
    br label %L278
L286:  
L287:  
L288:  
    br label %L284
    store i32 1, ptr %r16
    br label %L284
L289:  
L290:  
L291:  
    store i32 2, ptr %r16
    store i32 %r16, ptr %r20
    store i32 %r22, ptr %r18
    store i32 1, ptr %r19
    %r23 = icmp sge i32 %r19,%r21
    br i1 %r23, label %L372, label %L373
    %r22 = icmp slt i32 %r18,%r20
    br i1 %r22, label %L375, label %L376
    store i32 65535, ptr %r16
    br label %L377
    store i32 0, ptr %r16
    br label %L377
L292:  
L293:  
L294:  
    %r26 = alloca i32
    %r22 = alloca i32
    %r17 = alloca i32
    br i1 %r16, label %L297, label %L298
    store i32 2, ptr %r17
    store i32 %r25, ptr %r22
    br label %L300
    br i1 %r22, label %L301, label %L302
    store i32 65535, ptr %r16
    store i32 0, ptr %r17
    store i32 0, ptr %r18
    store i32 %r22, ptr %r19
    br label %L303
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L304, label %L305
    %r22 = srem i32 %r18,%r20
    br i1 %r22, label %L306, label %L307
    %r23 = srem i32 %r19,%r21
    %r27 = icmp eq i32 %r23,%r25
    br i1 %r27, label %L309, label %L310
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L311
L295:  
L297:  
    %r22 = sdiv i32 %r18,%r20
    store i32 0, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L292
L298:  
L300:  
    %r26 = alloca i32
    %r26 = alloca i32
    %r22 = alloca i32
    store i32 0, ptr %r22
    store i32 0, ptr %r26
    br label %L330
    br i1 %r26, label %L331, label %L332
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    store i32 %r22, ptr %r18
    store i32 %r26, ptr %r19
    br label %L333
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L334, label %L335
    %r22 = srem i32 %r18,%r20
    br i1 %r22, label %L336, label %L337
    %r23 = srem i32 %r19,%r21
    %r27 = icmp eq i32 %r23,%r25
    br i1 %r27, label %L339, label %L340
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L341
L301:  
L302:  
L303:  
    store i32 0, ptr %r16
    store i32 %r16, ptr %r21
    br label %L299
L304:  
L305:  
L306:  
    store i32 %r16, ptr %r26
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    store i32 0, ptr %r18
    store i32 %r22, ptr %r19
    br label %L315
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L316, label %L317
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r23,%r23
    br i1 %r25, label %L318, label %L319
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L320
L307:  
L308:  
L309:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L304
L310:  
L312:  
    br label %L308
    %r23 = srem i32 %r19,%r21
    br i1 %r23, label %L312, label %L313
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L314
L313:  
L315:  
    br label %L308
L316:  
L317:  
L318:  
    store i32 %r16, ptr %r22
    %r27 = icmp sgt i32 %r23,%r25
    br i1 %r27, label %L321, label %L322
    store i32 0, ptr %r16
    br label %L323
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    %r23 = load i32, ptr %r22
    %r25 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r24
    %r26 = load i32, ptr %r25
    %r27 = mul i32 %r23,%r26
    store i32 0, ptr %r18
    store i32 1, ptr %r19
    br label %L324
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L325, label %L326
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r23,%r23
    br i1 %r25, label %L327, label %L328
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L329
L319:  
L321:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L316
L322:  
L323:  
L324:  
    store i32 %r16, ptr %r22
    store i32 %r26, ptr %r17
    br label %L301
L325:  
L326:  
L327:  
    br label %L323
L328:  
L330:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L325
L331:  
L332:  
L333:  
    store i32 %r22, ptr %r16
    store i32 %r16, ptr %r25
    store i32 2, ptr %r18
    store i32 1, ptr %r19
    %r23 = icmp sge i32 %r19,%r21
    br i1 %r23, label %L360, label %L361
    %r22 = icmp slt i32 %r18,%r20
    br i1 %r22, label %L363, label %L364
    store i32 65535, ptr %r16
    br label %L365
    store i32 0, ptr %r16
    br label %L365
L334:  
L335:  
L336:  
    store i32 %r16, ptr %r26
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    store i32 %r22, ptr %r18
    store i32 %r26, ptr %r19
    br label %L345
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L346, label %L347
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r23,%r23
    br i1 %r25, label %L348, label %L349
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L350
L337:  
L338:  
L339:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L334
L340:  
L342:  
    br label %L338
    %r23 = srem i32 %r19,%r21
    br i1 %r23, label %L342, label %L343
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L344
L343:  
L345:  
    br label %L338
L346:  
L347:  
L348:  
    store i32 %r16, ptr %r26
    %r31 = icmp sgt i32 %r27,%r29
    br i1 %r31, label %L351, label %L352
    store i32 0, ptr %r16
    br label %L353
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    %r27 = load i32, ptr %r26
    %r29 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r28
    %r30 = load i32, ptr %r29
    %r31 = mul i32 %r27,%r30
    store i32 %r31, ptr %r18
    store i32 1, ptr %r19
    br label %L354
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L355, label %L356
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r23,%r23
    br i1 %r25, label %L357, label %L358
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L359
L349:  
L351:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L346
L352:  
L353:  
L354:  
    store i32 %r16, ptr %r26
    store i32 %r26, ptr %r22
    br label %L331
L355:  
L356:  
L357:  
    br label %L353
L358:  
L360:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L355
L361:  
L362:  
L363:  
    store i32 %r16, ptr %r21
    br label %L289
L364:  
L365:  
L366:  
    br label %L362
    %r23 = icmp sgt i32 %r19,%r21
    br i1 %r23, label %L366, label %L367
    %r22 = icmp sgt i32 %r18,%r20
    br i1 %r22, label %L369, label %L370
    %r20 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r19
    %r21 = load i32, ptr %r20
    %r22 = sdiv i32 %r18,%r21
    store i32 %r22, ptr %r18
    %r22 = add i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r21 = sub i32 %r24,%r19
    %r25 = add i32 %r21,%r23
    %r26 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r25
    %r27 = load i32, ptr %r26
    %r28 = sub i32 %r23,%r27
    store i32 0, ptr %r16
    br label %L371
    %r20 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r19
    %r21 = load i32, ptr %r20
    %r22 = sdiv i32 %r18,%r21
    store i32 %r22, ptr %r16
    br label %L371
L367:  
L368:  
L369:  
    br label %L362
L370:  
L371:  
L372:  
    br label %L368
    store i32 1, ptr %r16
    br label %L368
L373:  
L374:  
L375:  
    store i32 %r16, ptr %r22
    br label %L193
L376:  
L377:  
L378:  
    br label %L374
    %r23 = icmp sgt i32 %r19,%r21
    br i1 %r23, label %L378, label %L379
    %r22 = icmp sgt i32 %r18,%r20
    br i1 %r22, label %L381, label %L382
    %r20 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r19
    %r21 = load i32, ptr %r20
    %r22 = sdiv i32 %r18,%r21
    store i32 %r22, ptr %r18
    %r22 = add i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r21 = sub i32 %r24,%r19
    %r25 = add i32 %r21,%r23
    %r26 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r25
    %r27 = load i32, ptr %r26
    %r28 = sub i32 %r23,%r27
    store i32 0, ptr %r16
    br label %L383
    %r20 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r19
    %r21 = load i32, ptr %r20
    %r22 = sdiv i32 %r18,%r21
    store i32 %r22, ptr %r16
    br label %L383
L379:  
L380:  
L381:  
    br label %L374
L382:  
L383:  
L384:  
    br label %L380
    store i32 1, ptr %r16
    br label %L380
L385:  
L386:  
L387:  
    %r21 = alloca i32
    %r27 = alloca i32
    %r25 = alloca i32
    store i32 2, ptr %r20
    br label %L579
    %r24 = icmp slt i32 %r20,%r22
    br i1 %r24, label %L580, label %L581
    store i32 15, ptr %r25
    store i32 2, ptr %r27
    store i32 1, ptr %r21
    br label %L582
    %r28 = load i32, ptr %r27
    %r31 = icmp sgt i32 %r28,%r29
    br i1 %r31, label %L583, label %L584
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    store i32 %r27, ptr %r18
    store i32 1, ptr %r19
    br label %L585
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L586, label %L587
    %r22 = srem i32 %r18,%r20
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r22,%r23
    br i1 %r25, label %L588, label %L589
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 1, ptr %r16
    br label %L590
L388:  
L389:  
L390:  
    store i32 2, ptr %r16
    %r17 = call i32 @putint(i32 %r16)
    %r19 = call i32 @putch(i32 %r18)
    %r24 = add i32 %r20,%r22
    store i32 0, ptr %r20
    br label %L385
L391:  
L392:  
L393:  
    %r26 = alloca i32
    %r22 = alloca i32
    %r17 = alloca i32
    br i1 %r16, label %L396, label %L397
    store i32 2, ptr %r17
    store i32 %r25, ptr %r22
    store i32 0, ptr %r26
    br label %L399
    br i1 %r22, label %L400, label %L401
    store i32 65535, ptr %r16
    store i32 0, ptr %r17
    store i32 %r22, ptr %r18
    store i32 1, ptr %r19
    br label %L402
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L403, label %L404
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r23,%r23
    br i1 %r25, label %L405, label %L406
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L407
L394:  
L396:  
    %r22 = sdiv i32 %r18,%r20
    store i32 16, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L391
L397:  
L399:  
    %r26 = alloca i32
    %r26 = alloca i32
    %r22 = alloca i32
    store i32 0, ptr %r22
    store i32 0, ptr %r26
    store i32 0, ptr %r26
    br label %L483
    br i1 %r26, label %L484, label %L485
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    store i32 %r26, ptr %r18
    store i32 1, ptr %r19
    br label %L486
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L487, label %L488
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r23,%r23
    br i1 %r25, label %L489, label %L490
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L491
L400:  
L401:  
L402:  
    store i32 %r26, ptr %r16
    store i32 %r16, ptr %r21
    br label %L398
L403:  
L404:  
L405:  
    %r18 = alloca i32
    %r27 = alloca i32
    %r17 = alloca i32
    br i1 %r16, label %L408, label %L409
    store i32 %r26, ptr %r17
    store i32 %r17, ptr %r27
    br label %L411
    br i1 %r27, label %L412, label %L413
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    store i32 0, ptr %r18
    store i32 %r27, ptr %r19
    br label %L414
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L415, label %L416
    %r19 = load i32, ptr %r18
    %r22 = srem i32 %r19,%r20
    br i1 %r22, label %L417, label %L418
    %r23 = srem i32 %r19,%r21
    %r27 = icmp eq i32 %r23,%r25
    br i1 %r27, label %L420, label %L421
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L422
L406:  
L408:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L403
L409:  
L411:  
    %r18 = alloca i32
    %r18 = alloca i32
    %r27 = alloca i32
    store i32 0, ptr %r27
    store i32 0, ptr %r18
    br label %L441
    br i1 %r18, label %L442, label %L443
    store i32 1, ptr %r16
    store i32 0, ptr %r17
    store i32 %r27, ptr %r18
    store i32 %r18, ptr %r19
    br label %L444
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L445, label %L446
    %r19 = load i32, ptr %r18
    %r22 = srem i32 %r19,%r20
    br i1 %r22, label %L447, label %L448
    %r23 = srem i32 %r19,%r21
    %r27 = icmp eq i32 %r23,%r25
    br i1 %r27, label %L450, label %L451
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L452
L412:  
L413:  
L414:  
    store i32 0, ptr %r16
    store i32 %r16, ptr %r26
    br label %L410
L415:  
L416:  
L417:  
    store i32 %r16, ptr %r18
    store i32 1, ptr %r16
    store i32 0, ptr %r17
    store i32 0, ptr %r18
    store i32 %r27, ptr %r19
    br label %L426
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L427, label %L428
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r23,%r23
    br i1 %r25, label %L429, label %L430
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L431
L418:  
L419:  
L420:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L415
L421:  
L423:  
    br label %L419
    %r23 = srem i32 %r19,%r21
    br i1 %r23, label %L423, label %L424
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L425
L424:  
L426:  
    br label %L419
L427:  
L428:  
L429:  
    store i32 %r16, ptr %r27
    %r32 = icmp sgt i32 %r28,%r30
    br i1 %r32, label %L432, label %L433
    store i32 0, ptr %r16
    br label %L434
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    %r28 = load i32, ptr %r27
    %r30 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r29
    %r31 = load i32, ptr %r30
    %r32 = mul i32 %r28,%r31
    store i32 0, ptr %r18
    store i32 1, ptr %r19
    br label %L435
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L436, label %L437
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r23,%r23
    br i1 %r25, label %L438, label %L439
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L440
L430:  
L432:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L427
L433:  
L434:  
L435:  
    store i32 %r16, ptr %r27
    store i32 1, ptr %r17
    br label %L412
L436:  
L437:  
L438:  
    br label %L434
L439:  
L441:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L436
L442:  
L443:  
L444:  
    store i32 %r27, ptr %r16
    store i32 %r16, ptr %r17
    store i32 %r22, ptr %r18
    store i32 1, ptr %r19
    %r23 = icmp sge i32 %r19,%r21
    br i1 %r23, label %L471, label %L472
    %r22 = icmp slt i32 %r18,%r20
    br i1 %r22, label %L474, label %L475
    store i32 65535, ptr %r16
    br label %L476
    store i32 0, ptr %r16
    br label %L476
L445:  
L446:  
L447:  
    store i32 %r16, ptr %r18
    store i32 1, ptr %r16
    store i32 0, ptr %r17
    store i32 %r27, ptr %r18
    store i32 1, ptr %r19
    br label %L456
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L457, label %L458
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r23,%r23
    br i1 %r25, label %L459, label %L460
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L461
L448:  
L449:  
L450:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L445
L451:  
L453:  
    br label %L449
    %r23 = srem i32 %r19,%r21
    br i1 %r23, label %L453, label %L454
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L455
L454:  
L456:  
    br label %L449
L457:  
L458:  
L459:  
    store i32 %r16, ptr %r18
    %r23 = icmp sgt i32 %r19,%r21
    br i1 %r23, label %L462, label %L463
    store i32 0, ptr %r16
    br label %L464
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    %r21 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r20
    %r22 = load i32, ptr %r21
    %r23 = mul i32 %r18,%r22
    store i32 65535, ptr %r18
    store i32 1, ptr %r19
    br label %L465
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L466, label %L467
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r23,%r23
    br i1 %r25, label %L468, label %L469
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L470
L460:  
L462:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L457
L463:  
L464:  
L465:  
    store i32 %r16, ptr %r18
    store i32 1, ptr %r27
    br label %L442
L466:  
L467:  
L468:  
    br label %L464
L469:  
L471:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L466
L472:  
L473:  
L474:  
    store i32 %r16, ptr %r22
    br label %L400
L475:  
L476:  
L477:  
    br label %L473
    %r23 = icmp sgt i32 %r19,%r21
    br i1 %r23, label %L477, label %L478
    %r22 = icmp sgt i32 %r18,%r20
    br i1 %r22, label %L480, label %L481
    %r20 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r19
    %r21 = load i32, ptr %r20
    %r22 = sdiv i32 %r18,%r21
    store i32 %r22, ptr %r18
    %r22 = add i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r21 = sub i32 %r24,%r19
    %r25 = add i32 %r21,%r23
    %r26 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r25
    %r27 = load i32, ptr %r26
    %r28 = sub i32 %r23,%r27
    store i32 0, ptr %r16
    br label %L482
    %r20 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r19
    %r21 = load i32, ptr %r20
    %r22 = sdiv i32 %r18,%r21
    store i32 %r22, ptr %r16
    br label %L482
L478:  
L479:  
L480:  
    br label %L473
L481:  
L482:  
L483:  
    br label %L479
    store i32 1, ptr %r16
    br label %L479
L484:  
L485:  
L486:  
    store i32 15, ptr %r16
    store i32 %r16, ptr %r25
    store i32 %r27, ptr %r18
    store i32 1, ptr %r19
    %r23 = icmp sge i32 %r19,%r21
    br i1 %r23, label %L567, label %L568
    %r22 = icmp slt i32 %r18,%r20
    br i1 %r22, label %L570, label %L571
    store i32 65535, ptr %r16
    br label %L572
    store i32 0, ptr %r16
    br label %L572
L487:  
L488:  
L489:  
    %r23 = alloca i32
    %r27 = alloca i32
    %r17 = alloca i32
    br i1 %r16, label %L492, label %L493
    store i32 %r26, ptr %r17
    store i32 %r22, ptr %r27
    br label %L495
    br i1 %r27, label %L496, label %L497
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    store i32 0, ptr %r18
    store i32 %r27, ptr %r19
    br label %L498
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L499, label %L500
    %r22 = srem i32 %r18,%r20
    br i1 %r22, label %L501, label %L502
    %r23 = srem i32 %r19,%r21
    %r24 = load i32, ptr %r23
    %r27 = icmp eq i32 %r24,%r25
    br i1 %r27, label %L504, label %L505
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L506
L490:  
L492:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L487
L493:  
L495:  
    %r23 = alloca i32
    %r23 = alloca i32
    %r27 = alloca i32
    store i32 %r22, ptr %r27
    store i32 %r22, ptr %r23
    br label %L525
    br i1 %r23, label %L526, label %L527
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    store i32 %r27, ptr %r18
    store i32 %r23, ptr %r19
    br label %L528
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L529, label %L530
    %r22 = srem i32 %r18,%r20
    br i1 %r22, label %L531, label %L532
    %r23 = srem i32 %r19,%r21
    %r24 = load i32, ptr %r23
    %r27 = icmp eq i32 %r24,%r25
    br i1 %r27, label %L534, label %L535
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L536
L496:  
L497:  
L498:  
    store i32 0, ptr %r16
    store i32 %r16, ptr %r26
    br label %L494
L499:  
L500:  
L501:  
    store i32 %r16, ptr %r23
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    store i32 0, ptr %r18
    store i32 %r27, ptr %r19
    br label %L510
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L511, label %L512
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r24 = load i32, ptr %r23
    %r25 = and i32 %r23,%r24
    br i1 %r25, label %L513, label %L514
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L515
L502:  
L503:  
L504:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 %r23, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L499
L505:  
L507:  
    br label %L503
    %r23 = srem i32 %r19,%r21
    br i1 %r23, label %L507, label %L508
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L509
L508:  
L510:  
    br label %L503
L511:  
L512:  
L513:  
    store i32 %r16, ptr %r27
    %r32 = icmp sgt i32 %r28,%r30
    br i1 %r32, label %L516, label %L517
    store i32 0, ptr %r16
    br label %L518
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    %r28 = load i32, ptr %r27
    %r30 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r29
    %r31 = load i32, ptr %r30
    %r32 = mul i32 %r28,%r31
    store i32 0, ptr %r18
    store i32 1, ptr %r19
    br label %L519
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L520, label %L521
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r24 = load i32, ptr %r23
    %r25 = and i32 %r23,%r24
    br i1 %r25, label %L522, label %L523
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L524
L514:  
L516:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 %r23, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L511
L517:  
L518:  
L519:  
    store i32 %r16, ptr %r27
    store i32 %r23, ptr %r17
    br label %L496
L520:  
L521:  
L522:  
    br label %L518
L523:  
L525:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 %r23, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L520
L526:  
L527:  
L528:  
    store i32 %r27, ptr %r16
    store i32 %r16, ptr %r22
    store i32 15, ptr %r18
    store i32 1, ptr %r19
    %r23 = icmp sge i32 %r19,%r21
    br i1 %r23, label %L555, label %L556
    %r22 = icmp slt i32 %r18,%r20
    br i1 %r22, label %L558, label %L559
    store i32 65535, ptr %r16
    br label %L560
    store i32 0, ptr %r16
    br label %L560
L529:  
L530:  
L531:  
    store i32 %r16, ptr %r23
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    store i32 %r27, ptr %r18
    store i32 %r23, ptr %r19
    br label %L540
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L541, label %L542
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r24 = load i32, ptr %r23
    %r25 = and i32 %r23,%r24
    br i1 %r25, label %L543, label %L544
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L545
L532:  
L533:  
L534:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 %r23, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L529
L535:  
L537:  
    br label %L533
    %r23 = srem i32 %r19,%r21
    br i1 %r23, label %L537, label %L538
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L539
L538:  
L540:  
    br label %L533
L541:  
L542:  
L543:  
    store i32 %r16, ptr %r23
    %r28 = icmp sgt i32 %r24,%r26
    br i1 %r28, label %L546, label %L547
    store i32 0, ptr %r16
    br label %L548
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    %r24 = load i32, ptr %r23
    %r26 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r25
    %r27 = load i32, ptr %r26
    %r28 = mul i32 %r24,%r27
    store i32 0, ptr %r18
    store i32 1, ptr %r19
    br label %L549
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L550, label %L551
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r24 = load i32, ptr %r23
    %r25 = and i32 %r23,%r24
    br i1 %r25, label %L552, label %L553
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L554
L544:  
L546:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 %r23, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L541
L547:  
L548:  
L549:  
    store i32 %r16, ptr %r23
    store i32 %r23, ptr %r27
    br label %L526
L550:  
L551:  
L552:  
    br label %L548
L553:  
L555:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 %r23, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L550
L556:  
L557:  
L558:  
    store i32 %r16, ptr %r26
    br label %L484
L559:  
L560:  
L561:  
    br label %L557
    %r23 = icmp sgt i32 %r19,%r21
    br i1 %r23, label %L561, label %L562
    %r22 = icmp sgt i32 %r18,%r20
    br i1 %r22, label %L564, label %L565
    %r20 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r19
    %r21 = load i32, ptr %r20
    %r22 = sdiv i32 %r18,%r21
    store i32 %r22, ptr %r18
    %r22 = add i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r21 = sub i32 %r24,%r19
    %r25 = add i32 %r21,%r23
    %r26 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r25
    %r27 = load i32, ptr %r26
    %r28 = sub i32 %r23,%r27
    store i32 0, ptr %r16
    br label %L566
    %r20 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r19
    %r21 = load i32, ptr %r20
    %r22 = sdiv i32 %r18,%r21
    store i32 %r22, ptr %r16
    br label %L566
L562:  
L563:  
L564:  
    br label %L557
L565:  
L566:  
L567:  
    br label %L563
    store i32 1, ptr %r16
    br label %L563
L568:  
L569:  
L570:  
    store i32 %r16, ptr %r27
    br label %L388
L571:  
L572:  
L573:  
    br label %L569
    %r23 = icmp sgt i32 %r19,%r21
    br i1 %r23, label %L573, label %L574
    %r22 = icmp sgt i32 %r18,%r20
    br i1 %r22, label %L576, label %L577
    %r20 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r19
    %r21 = load i32, ptr %r20
    %r22 = sdiv i32 %r18,%r21
    store i32 %r22, ptr %r18
    %r22 = add i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r21 = sub i32 %r24,%r19
    %r25 = add i32 %r21,%r23
    %r26 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r25
    %r27 = load i32, ptr %r26
    %r28 = sub i32 %r23,%r27
    store i32 0, ptr %r16
    br label %L578
    %r20 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r19
    %r21 = load i32, ptr %r20
    %r22 = sdiv i32 %r18,%r21
    store i32 %r22, ptr %r16
    br label %L578
L574:  
L575:  
L576:  
    br label %L569
L577:  
L578:  
L579:  
    br label %L575
    store i32 1, ptr %r16
    br label %L575
L580:  
L581:  
L582:  
    ret i32 2
L583:  
L584:  
L585:  
    store i32 2, ptr %r16
    %r21 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r20
    %r22 = load i32, ptr %r21
    %r17 = load i32, ptr %r16
    %r18 = icmp ne i32 %r22,%r17
    br i1 %r18, label %L774, label %L775
    ret i32 1
    br label %L776
L586:  
L587:  
L588:  
    %r26 = alloca i32
    %r22 = alloca i32
    %r17 = alloca i32
    br i1 %r16, label %L591, label %L592
    store i32 2, ptr %r17
    store i32 %r25, ptr %r22
    store i32 0, ptr %r26
    br label %L594
    br i1 %r22, label %L595, label %L596
    store i32 65535, ptr %r16
    store i32 0, ptr %r17
    store i32 %r22, ptr %r18
    store i32 1, ptr %r19
    br label %L597
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L598, label %L599
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r23,%r23
    br i1 %r25, label %L600, label %L601
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L602
L589:  
L591:  
    %r22 = sdiv i32 %r18,%r20
    store i32 1, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L586
L592:  
L594:  
    %r26 = alloca i32
    %r26 = alloca i32
    %r22 = alloca i32
    store i32 0, ptr %r22
    store i32 0, ptr %r26
    store i32 0, ptr %r26
    br label %L678
    br i1 %r26, label %L679, label %L680
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    store i32 %r26, ptr %r18
    store i32 1, ptr %r19
    br label %L681
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L682, label %L683
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r23,%r23
    br i1 %r25, label %L684, label %L685
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L686
L595:  
L596:  
L597:  
    store i32 %r26, ptr %r16
    store i32 %r16, ptr %r21
    br label %L593
L598:  
L599:  
L600:  
    %r18 = alloca i32
    %r27 = alloca i32
    %r17 = alloca i32
    br i1 %r16, label %L603, label %L604
    store i32 %r26, ptr %r17
    store i32 %r17, ptr %r27
    br label %L606
    br i1 %r27, label %L607, label %L608
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    store i32 0, ptr %r18
    store i32 %r27, ptr %r19
    br label %L609
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L610, label %L611
    %r19 = load i32, ptr %r18
    %r22 = srem i32 %r19,%r20
    br i1 %r22, label %L612, label %L613
    %r23 = srem i32 %r19,%r21
    %r27 = icmp eq i32 %r23,%r25
    br i1 %r27, label %L615, label %L616
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L617
L601:  
L603:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L598
L604:  
L606:  
    %r18 = alloca i32
    %r18 = alloca i32
    %r27 = alloca i32
    store i32 0, ptr %r27
    store i32 0, ptr %r18
    br label %L636
    br i1 %r18, label %L637, label %L638
    store i32 1, ptr %r16
    store i32 0, ptr %r17
    store i32 %r27, ptr %r18
    store i32 %r18, ptr %r19
    br label %L639
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L640, label %L641
    %r19 = load i32, ptr %r18
    %r22 = srem i32 %r19,%r20
    br i1 %r22, label %L642, label %L643
    %r23 = srem i32 %r19,%r21
    %r27 = icmp eq i32 %r23,%r25
    br i1 %r27, label %L645, label %L646
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L647
L607:  
L608:  
L609:  
    store i32 0, ptr %r16
    store i32 %r16, ptr %r26
    br label %L605
L610:  
L611:  
L612:  
    store i32 %r16, ptr %r18
    store i32 1, ptr %r16
    store i32 0, ptr %r17
    store i32 0, ptr %r18
    store i32 %r27, ptr %r19
    br label %L621
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L622, label %L623
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r23,%r23
    br i1 %r25, label %L624, label %L625
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L626
L613:  
L614:  
L615:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L610
L616:  
L618:  
    br label %L614
    %r23 = srem i32 %r19,%r21
    br i1 %r23, label %L618, label %L619
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L620
L619:  
L621:  
    br label %L614
L622:  
L623:  
L624:  
    store i32 %r16, ptr %r27
    %r32 = icmp sgt i32 %r28,%r30
    br i1 %r32, label %L627, label %L628
    store i32 0, ptr %r16
    br label %L629
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    %r28 = load i32, ptr %r27
    %r30 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r29
    %r31 = load i32, ptr %r30
    %r32 = mul i32 %r28,%r31
    store i32 0, ptr %r18
    store i32 1, ptr %r19
    br label %L630
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L631, label %L632
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r23,%r23
    br i1 %r25, label %L633, label %L634
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L635
L625:  
L627:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L622
L628:  
L629:  
L630:  
    store i32 %r16, ptr %r27
    store i32 1, ptr %r17
    br label %L607
L631:  
L632:  
L633:  
    br label %L629
L634:  
L636:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L631
L637:  
L638:  
L639:  
    store i32 %r27, ptr %r16
    store i32 %r16, ptr %r17
    store i32 %r22, ptr %r18
    store i32 1, ptr %r19
    %r23 = icmp sge i32 %r19,%r21
    br i1 %r23, label %L666, label %L667
    %r22 = icmp slt i32 %r18,%r20
    br i1 %r22, label %L669, label %L670
    store i32 65535, ptr %r16
    br label %L671
    store i32 0, ptr %r16
    br label %L671
L640:  
L641:  
L642:  
    store i32 %r16, ptr %r18
    store i32 1, ptr %r16
    store i32 0, ptr %r17
    store i32 %r27, ptr %r18
    store i32 1, ptr %r19
    br label %L651
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L652, label %L653
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r23,%r23
    br i1 %r25, label %L654, label %L655
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L656
L643:  
L644:  
L645:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L640
L646:  
L648:  
    br label %L644
    %r23 = srem i32 %r19,%r21
    br i1 %r23, label %L648, label %L649
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L650
L649:  
L651:  
    br label %L644
L652:  
L653:  
L654:  
    store i32 %r16, ptr %r18
    %r23 = icmp sgt i32 %r19,%r21
    br i1 %r23, label %L657, label %L658
    store i32 0, ptr %r16
    br label %L659
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    %r21 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r20
    %r22 = load i32, ptr %r21
    %r23 = mul i32 %r18,%r22
    store i32 65535, ptr %r18
    store i32 1, ptr %r19
    br label %L660
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L661, label %L662
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r25 = and i32 %r23,%r23
    br i1 %r25, label %L663, label %L664
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L665
L655:  
L657:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L652
L658:  
L659:  
L660:  
    store i32 %r16, ptr %r18
    store i32 1, ptr %r27
    br label %L637
L661:  
L662:  
L663:  
    br label %L659
L664:  
L666:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L661
L667:  
L668:  
L669:  
    store i32 %r16, ptr %r22
    br label %L595
L670:  
L671:  
L672:  
    br label %L668
    %r23 = icmp sgt i32 %r19,%r21
    br i1 %r23, label %L672, label %L673
    %r22 = icmp sgt i32 %r18,%r20
    br i1 %r22, label %L675, label %L676
    %r20 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r19
    %r21 = load i32, ptr %r20
    %r22 = sdiv i32 %r18,%r21
    store i32 %r22, ptr %r18
    %r22 = add i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r21 = sub i32 %r24,%r19
    %r25 = add i32 %r21,%r23
    %r26 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r25
    %r27 = load i32, ptr %r26
    %r28 = sub i32 %r23,%r27
    store i32 0, ptr %r16
    br label %L677
    %r20 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r19
    %r21 = load i32, ptr %r20
    %r22 = sdiv i32 %r18,%r21
    store i32 %r22, ptr %r16
    br label %L677
L673:  
L674:  
L675:  
    br label %L668
L676:  
L677:  
L678:  
    br label %L674
    store i32 1, ptr %r16
    br label %L674
L679:  
L680:  
L681:  
    store i32 15, ptr %r16
    store i32 %r16, ptr %r25
    store i32 %r27, ptr %r18
    store i32 1, ptr %r19
    %r23 = icmp sge i32 %r19,%r21
    br i1 %r23, label %L762, label %L763
    %r22 = icmp slt i32 %r18,%r20
    br i1 %r22, label %L765, label %L766
    store i32 65535, ptr %r16
    br label %L767
    store i32 0, ptr %r16
    br label %L767
L682:  
L683:  
L684:  
    %r23 = alloca i32
    %r27 = alloca i32
    %r17 = alloca i32
    br i1 %r16, label %L687, label %L688
    store i32 %r26, ptr %r17
    store i32 %r22, ptr %r27
    br label %L690
    br i1 %r27, label %L691, label %L692
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    store i32 0, ptr %r18
    store i32 %r27, ptr %r19
    br label %L693
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L694, label %L695
    %r22 = srem i32 %r18,%r20
    br i1 %r22, label %L696, label %L697
    %r23 = srem i32 %r19,%r21
    %r24 = load i32, ptr %r23
    %r27 = icmp eq i32 %r24,%r25
    br i1 %r27, label %L699, label %L700
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L701
L685:  
L687:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 65535, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L682
L688:  
L690:  
    %r23 = alloca i32
    %r23 = alloca i32
    %r27 = alloca i32
    store i32 %r22, ptr %r27
    store i32 %r22, ptr %r23
    br label %L720
    br i1 %r23, label %L721, label %L722
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    store i32 %r27, ptr %r18
    store i32 %r23, ptr %r19
    br label %L723
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L724, label %L725
    %r22 = srem i32 %r18,%r20
    br i1 %r22, label %L726, label %L727
    %r23 = srem i32 %r19,%r21
    %r24 = load i32, ptr %r23
    %r27 = icmp eq i32 %r24,%r25
    br i1 %r27, label %L729, label %L730
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L731
L691:  
L692:  
L693:  
    store i32 0, ptr %r16
    store i32 %r16, ptr %r26
    br label %L689
L694:  
L695:  
L696:  
    store i32 %r16, ptr %r23
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    store i32 0, ptr %r18
    store i32 %r27, ptr %r19
    br label %L705
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L706, label %L707
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r24 = load i32, ptr %r23
    %r25 = and i32 %r23,%r24
    br i1 %r25, label %L708, label %L709
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L710
L697:  
L698:  
L699:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 %r23, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L694
L700:  
L702:  
    br label %L698
    %r23 = srem i32 %r19,%r21
    br i1 %r23, label %L702, label %L703
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L704
L703:  
L705:  
    br label %L698
L706:  
L707:  
L708:  
    store i32 %r16, ptr %r27
    %r32 = icmp sgt i32 %r28,%r30
    br i1 %r32, label %L711, label %L712
    store i32 0, ptr %r16
    br label %L713
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    %r28 = load i32, ptr %r27
    %r30 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r29
    %r31 = load i32, ptr %r30
    %r32 = mul i32 %r28,%r31
    store i32 0, ptr %r18
    store i32 1, ptr %r19
    br label %L714
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L715, label %L716
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r24 = load i32, ptr %r23
    %r25 = and i32 %r23,%r24
    br i1 %r25, label %L717, label %L718
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L719
L709:  
L711:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 %r23, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L706
L712:  
L713:  
L714:  
    store i32 %r16, ptr %r27
    store i32 %r23, ptr %r17
    br label %L691
L715:  
L716:  
L717:  
    br label %L713
L718:  
L720:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 %r23, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L715
L721:  
L722:  
L723:  
    store i32 %r27, ptr %r16
    store i32 %r16, ptr %r22
    store i32 15, ptr %r18
    store i32 1, ptr %r19
    %r23 = icmp sge i32 %r19,%r21
    br i1 %r23, label %L750, label %L751
    %r22 = icmp slt i32 %r18,%r20
    br i1 %r22, label %L753, label %L754
    store i32 65535, ptr %r16
    br label %L755
    store i32 0, ptr %r16
    br label %L755
L724:  
L725:  
L726:  
    store i32 %r16, ptr %r23
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    store i32 %r27, ptr %r18
    store i32 %r23, ptr %r19
    br label %L735
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L736, label %L737
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r24 = load i32, ptr %r23
    %r25 = and i32 %r23,%r24
    br i1 %r25, label %L738, label %L739
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L740
L727:  
L728:  
L729:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 %r23, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L724
L730:  
L732:  
    br label %L728
    %r23 = srem i32 %r19,%r21
    br i1 %r23, label %L732, label %L733
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L734
L733:  
L735:  
    br label %L728
L736:  
L737:  
L738:  
    store i32 %r16, ptr %r23
    %r28 = icmp sgt i32 %r24,%r26
    br i1 %r28, label %L741, label %L742
    store i32 0, ptr %r16
    br label %L743
    store i32 0, ptr %r16
    store i32 0, ptr %r17
    %r24 = load i32, ptr %r23
    %r26 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r25
    %r27 = load i32, ptr %r26
    %r28 = mul i32 %r24,%r27
    store i32 0, ptr %r18
    store i32 1, ptr %r19
    br label %L744
    %r21 = icmp slt i32 %r17,%r19
    br i1 %r21, label %L745, label %L746
    %r22 = srem i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r23 = srem i32 %r19,%r21
    %r24 = load i32, ptr %r23
    %r25 = and i32 %r23,%r24
    br i1 %r25, label %L747, label %L748
    %r17 = load i32, ptr %r16
    %r18 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r17
    %r19 = load i32, ptr %r18
    %r20 = mul i32 %r18,%r19
    %r21 = load i32, ptr %r20
    %r22 = add i32 %r17,%r21
    store i32 %r22, ptr %r16
    br label %L749
L739:  
L741:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 %r23, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L736
L742:  
L743:  
L744:  
    store i32 %r16, ptr %r23
    store i32 %r23, ptr %r27
    br label %L721
L745:  
L746:  
L747:  
    br label %L743
L748:  
L750:  
    %r22 = sdiv i32 %r18,%r20
    store i32 %r22, ptr %r18
    %r23 = sdiv i32 %r19,%r21
    store i32 %r23, ptr %r19
    %r21 = add i32 %r17,%r19
    store i32 2, ptr %r17
    br label %L745
L751:  
L752:  
L753:  
    store i32 %r16, ptr %r26
    br label %L679
L754:  
L755:  
L756:  
    br label %L752
    %r23 = icmp sgt i32 %r19,%r21
    br i1 %r23, label %L756, label %L757
    %r22 = icmp sgt i32 %r18,%r20
    br i1 %r22, label %L759, label %L760
    %r20 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r19
    %r21 = load i32, ptr %r20
    %r22 = sdiv i32 %r18,%r21
    store i32 %r22, ptr %r18
    %r22 = add i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r21 = sub i32 %r24,%r19
    %r25 = add i32 %r21,%r23
    %r26 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r25
    %r27 = load i32, ptr %r26
    %r28 = sub i32 %r23,%r27
    store i32 0, ptr %r16
    br label %L761
    %r20 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r19
    %r21 = load i32, ptr %r20
    %r22 = sdiv i32 %r18,%r21
    store i32 %r22, ptr %r16
    br label %L761
L757:  
L758:  
L759:  
    br label %L752
L760:  
L761:  
L762:  
    br label %L758
    store i32 1, ptr %r16
    br label %L758
L763:  
L764:  
L765:  
    store i32 %r16, ptr %r27
    br label %L583
L766:  
L767:  
L768:  
    br label %L764
    %r23 = icmp sgt i32 %r19,%r21
    br i1 %r23, label %L768, label %L769
    %r22 = icmp sgt i32 %r18,%r20
    br i1 %r22, label %L771, label %L772
    %r20 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r19
    %r21 = load i32, ptr %r20
    %r22 = sdiv i32 %r18,%r21
    store i32 %r22, ptr %r18
    %r22 = add i32 %r18,%r20
    %r23 = load i32, ptr %r22
    %r21 = sub i32 %r24,%r19
    %r25 = add i32 %r21,%r23
    %r26 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r25
    %r27 = load i32, ptr %r26
    %r28 = sub i32 %r23,%r27
    store i32 0, ptr %r16
    br label %L773
    %r20 = getelementptr [16 x i32], ptr @SHIFT_TABLE, i32 0, i32 %r19
    %r21 = load i32, ptr %r20
    %r22 = sdiv i32 %r18,%r21
    store i32 %r22, ptr %r16
    br label %L773
L769:  
L770:  
L771:  
    br label %L764
L772:  
L773:  
L774:  
    br label %L770
    store i32 1, ptr %r16
    br label %L770
L775:  
L777:  
    %r24 = add i32 %r20,%r22
    store i32 0, ptr %r20
    br label %L580
}
define i32 @main()
{
L1:  
    %r22 = call i32 @long_func()
    ret i32 1
}
