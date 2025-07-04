@pos = global i32 0
@buffer = global [50000000x i32] zeroinitializer
define i32 @is_number(i32 %r0)
{
L1:  
    %r2 = load i32, ptr %r1
    %r5 = icmp sle i32 %r2,%r3
    br i1 %r5, label %L3, label %L4
    ret i32 1
    br label %L5
    ret i32 0
    br label %L5
L2:  
L3:  
L4:  
L5:  
L6:  
    br label %L2
    ret i32 0
    br label %L2
}
define i32 @detect_item(i32 %r0,i32 %r61,i32 %r2)
{
L1:  
    %r64 = load i32, ptr @pos
    %r65 = load i32, ptr %r64
    %r64 = load i32, ptr %r63
    %r65 = icmp sge i32 %r65,%r64
    br i1 %r65, label %L24, label %L25
    ret i32 0
    br label %L26
L25:  
L27:  
    %r64 = call i32 @skip_space(i32 %r62,i32 %r63)
    %r62 = load i32, ptr %r61
    %r65 = icmp eq i32 %r62,%r63
    br i1 %r65, label %L27, label %L28
    %r66 = load i32, ptr @pos
    %r67 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r66
    %r68 = load float, ptr %r67
    %r71 = icmp eq i32 %r68,%r69
    br i1 %r71, label %L30, label %L31
    %r64 = call i32 @detect_item(i32 %r72,i32 %r62,i32 %r63)
    ret i32 %r64
    br label %L32
    %r65 = load i32, ptr @pos
    %r66 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r65
    %r67 = load i32, ptr %r66
    %r70 = icmp eq i32 %r67,%r68
    br i1 %r70, label %L33, label %L34
    %r64 = call i32 @detect_item(i32 %r71,i32 %r62,i32 %r63)
    ret i32 %r64
    br label %L35
    %r65 = load i32, ptr @pos
    %r66 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r65
    %r67 = load i32, ptr %r66
    %r70 = icmp eq i32 %r67,%r68
    br i1 %r70, label %L36, label %L37
    %r64 = call i32 @detect_item(i32 %r71,i32 %r62,i32 %r63)
    ret i32 %r64
    br label %L38
    %r65 = load i32, ptr @pos
    %r66 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r65
    %r67 = call i32 @is_number(i32 %r66)
    %r68 = load float, ptr %r67
    %r71 = icmp eq i32 %r68,%r69
    br i1 %r71, label %L39, label %L40
    %r64 = call i32 @detect_item(i32 %r72,i32 %r62,i32 %r63)
    ret i32 %r64
    br label %L41
    %r65 = load i32, ptr @pos
    %r66 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r65
    %r67 = load i32, ptr %r66
    %r70 = icmp eq i32 %r67,%r68
    br i1 %r70, label %L42, label %L43
    %r64 = call i32 @detect_item(i32 %r71,i32 %r62,i32 %r63)
    ret i32 %r64
    br label %L44
    %r65 = load i32, ptr @pos
    %r66 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r65
    %r67 = load i32, ptr %r66
    %r70 = icmp eq i32 %r67,%r68
    br i1 %r70, label %L45, label %L46
    %r64 = call i32 @detect_item(i32 %r71,i32 %r62,i32 %r63)
    ret i32 %r64
    br label %L47
    %r65 = load i32, ptr @pos
    %r66 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r65
    %r67 = load i32, ptr %r66
    %r70 = icmp eq i32 %r67,%r68
    br i1 %r70, label %L48, label %L49
    %r64 = call i32 @detect_item(i32 %r71,i32 %r62,i32 %r63)
    ret i32 %r64
    br label %L50
    %r65 = load i32, ptr @pos
    %r66 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r65
    %r67 = load i32, ptr %r66
    %r70 = icmp eq i32 %r67,%r68
    br i1 %r70, label %L51, label %L52
    %r64 = call i32 @detect_item(i32 %r71,i32 %r62,i32 %r63)
    ret i32 %r64
    br label %L53
    %r65 = load i32, ptr @pos
    %r66 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r65
    %r67 = load i32, ptr %r66
    %r70 = icmp eq i32 %r67,%r68
    br i1 %r70, label %L54, label %L55
    %r64 = call i32 @detect_item(i32 %r71,i32 %r62,i32 %r63)
    ret i32 %r64
    br label %L56
    ret i32 0
    br label %L56
L28:  
L29:  
L30:  
    ret i32 4
L31:  
L32:  
L33:  
    br label %L29
    %r62 = load i32, ptr %r61
    %r65 = icmp eq i32 %r62,%r63
    br i1 %r65, label %L57, label %L58
    %r66 = load i32, ptr @pos
    %r67 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r66
    %r68 = load float, ptr %r67
    %r71 = icmp eq i32 %r68,%r69
    br i1 %r71, label %L60, label %L61
    %r72 = load i32, ptr @pos
    %r73 = load i32, ptr %r72
    %r76 = add i32 %r73,%r74
    %r77 = load i32, ptr @pos
    store i32 %r76, ptr %r77
    br label %L62
    %r78 = load i32, ptr @pos
    %r79 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r78
    %r80 = load float, ptr %r79
    %r83 = icmp eq i32 %r80,%r81
    br i1 %r83, label %L63, label %L64
    %r84 = load i32, ptr @pos
    %r85 = load i32, ptr %r84
    %r88 = add i32 %r85,%r86
    %r89 = load i32, ptr @pos
    store i32 %r88, ptr %r89
    br label %L65
L34:  
L35:  
L36:  
    br label %L32
L37:  
L38:  
L39:  
    br label %L35
L40:  
L41:  
L42:  
    br label %L38
L43:  
L44:  
L45:  
    br label %L41
L46:  
L47:  
L48:  
    br label %L44
L49:  
L50:  
L51:  
    br label %L47
L52:  
L53:  
L54:  
    br label %L50
L55:  
L56:  
L57:  
    br label %L53
L58:  
L59:  
L60:  
    br label %L29
L61:  
L62:  
L63:  
    %r90 = load i32, ptr @pos
    %r91 = load i32, ptr %r90
    %r65 = icmp sge i32 %r91,%r63
    br i1 %r65, label %L66, label %L67
    ret i32 0
    br label %L68
    %r67 = load i32, ptr @pos
    %r68 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r67
    %r69 = call i32 @is_number(i32 %r68)
    %r73 = icmp eq i32 %r69,%r71
    br i1 %r73, label %L69, label %L70
    ret i32 1
    br label %L71
L64:  
L66:  
    br label %L62
L67:  
L68:  
L69:  
    br label %L72
    %r75 = load i32, ptr @pos
    %r76 = load i32, ptr %r75
    %r65 = icmp slt i32 %r76,%r63
    br i1 %r65, label %L73, label %L74
    %r66 = load i32, ptr @pos
    %r67 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r66
    %r68 = call i32 @is_number(i32 %r67)
    %r72 = icmp ne i32 %r68,%r70
    br i1 %r72, label %L75, label %L76
    br label %L74
    br label %L77
L70:  
L72:  
    br label %L68
L73:  
L74:  
L75:  
    %r79 = load i32, ptr @pos
    %r80 = load i32, ptr %r79
    %r65 = icmp slt i32 %r80,%r63
    br i1 %r65, label %L78, label %L79
    %r66 = load i32, ptr @pos
    %r67 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r66
    %r68 = load i32, ptr %r67
    %r71 = icmp eq i32 %r68,%r69
    br i1 %r71, label %L81, label %L82
    %r72 = load i32, ptr @pos
    %r73 = load i32, ptr %r72
    %r76 = add i32 %r73,%r74
    %r77 = load i32, ptr @pos
    store i32 %r76, ptr %r77
    br label %L84
    %r78 = load i32, ptr @pos
    %r79 = load i32, ptr %r78
    %r65 = icmp slt i32 %r79,%r63
    br i1 %r65, label %L85, label %L86
    %r66 = load i32, ptr @pos
    %r67 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r66
    %r68 = call i32 @is_number(i32 %r67)
    %r72 = icmp ne i32 %r68,%r70
    br i1 %r72, label %L87, label %L88
    br label %L86
    br label %L89
L76:  
L78:  
    %r73 = load i32, ptr @pos
    %r74 = load i32, ptr %r73
    %r77 = add i32 %r74,%r75
    %r78 = load i32, ptr @pos
    store i32 %r77, ptr %r78
    br label %L73
L79:  
L81:  
    %r79 = load i32, ptr @pos
    %r80 = load i32, ptr %r79
    %r65 = icmp slt i32 %r80,%r63
    br i1 %r65, label %L90, label %L91
    %r66 = load i32, ptr @pos
    %r67 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r66
    %r68 = load i32, ptr %r67
    %r71 = icmp eq i32 %r68,%r69
    br i1 %r71, label %L93, label %L94
    %r72 = load i32, ptr @pos
    %r73 = load i32, ptr %r72
    %r76 = add i32 %r73,%r74
    %r77 = load i32, ptr @pos
    store i32 %r76, ptr %r77
    %r78 = load i32, ptr @pos
    %r79 = load i32, ptr %r78
    %r65 = icmp slt i32 %r79,%r63
    br i1 %r65, label %L96, label %L97
    %r66 = load i32, ptr @pos
    %r67 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r66
    %r68 = load i32, ptr %r67
    %r71 = icmp eq i32 %r68,%r69
    br i1 %r71, label %L99, label %L100
    %r72 = load i32, ptr @pos
    %r73 = load i32, ptr %r72
    %r76 = add i32 %r73,%r74
    %r77 = load i32, ptr @pos
    store i32 %r76, ptr %r77
    br label %L101
L82:  
L84:  
    br label %L80
L85:  
L86:  
L87:  
    br label %L83
L88:  
L90:  
    %r73 = load i32, ptr @pos
    %r74 = load i32, ptr %r73
    %r77 = add i32 %r74,%r75
    %r78 = load i32, ptr @pos
    store i32 %r77, ptr %r78
    br label %L85
L91:  
L93:  
    br label %L59
    %r62 = load i32, ptr %r61
    %r65 = icmp eq i32 %r62,%r63
    br i1 %r65, label %L114, label %L115
    %r66 = load i32, ptr @pos
    %r67 = load i32, ptr %r66
    %r70 = add i32 %r67,%r68
    %r71 = load i32, ptr @pos
    store i32 1, ptr %r71
    br label %L117
    %r72 = load i32, ptr @pos
    %r73 = load i32, ptr %r72
    %r65 = icmp slt i32 %r73,%r63
    br i1 %r65, label %L118, label %L119
    %r66 = load i32, ptr @pos
    %r67 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r66
    %r68 = load i32, ptr %r67
    %r71 = icmp eq i32 %r68,%r69
    br i1 %r71, label %L120, label %L121
    br label %L119
    br label %L122
L94:  
L96:  
    br label %L92
L97:  
L99:  
    %r78 = load i32, ptr @pos
    %r79 = load i32, ptr %r78
    %r65 = icmp slt i32 %r79,%r63
    br i1 %r65, label %L102, label %L103
    %r66 = load i32, ptr @pos
    %r67 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r66
    %r68 = load i32, ptr %r67
    %r71 = icmp eq i32 %r68,%r69
    br i1 %r71, label %L105, label %L106
    %r72 = load i32, ptr @pos
    %r73 = load i32, ptr %r72
    %r76 = add i32 %r73,%r74
    %r77 = load i32, ptr @pos
    store i32 %r76, ptr %r77
    br label %L107
L100:  
L102:  
    br label %L98
L103:  
L105:  
    br label %L108
    %r78 = load i32, ptr @pos
    %r79 = load i32, ptr %r78
    %r65 = icmp slt i32 %r79,%r63
    br i1 %r65, label %L109, label %L110
    %r66 = load i32, ptr @pos
    %r67 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r66
    %r68 = call i32 @is_number(i32 %r67)
    %r72 = icmp ne i32 %r68,%r70
    br i1 %r72, label %L111, label %L112
    br label %L110
    br label %L113
L106:  
L108:  
    br label %L104
L109:  
L110:  
L111:  
    br label %L95
L112:  
L114:  
    %r73 = load i32, ptr @pos
    %r74 = load i32, ptr %r73
    %r77 = add i32 %r74,%r75
    %r78 = load i32, ptr @pos
    store i32 %r77, ptr %r78
    br label %L109
L115:  
L116:  
L117:  
    br label %L59
L118:  
L119:  
L120:  
    %r90 = load i32, ptr @pos
    %r91 = load i32, ptr %r90
    %r65 = icmp sge i32 %r91,%r63
    br i1 %r65, label %L126, label %L127
    ret i32 0
    br label %L128
    %r67 = load i32, ptr @pos
    %r68 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r67
    %r72 = icmp ne i32 %r68,%r70
    br i1 %r72, label %L129, label %L130
    ret i32 0
    br label %L131
L121:  
L123:  
    %r72 = load i32, ptr @pos
    %r73 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r72
    %r74 = load i32, ptr %r73
    %r77 = icmp eq i32 %r74,%r75
    br i1 %r77, label %L123, label %L124
    %r78 = load i32, ptr @pos
    %r79 = load i32, ptr %r78
    %r82 = add i32 %r79,%r80
    %r83 = load i32, ptr @pos
    store i32 %r82, ptr %r83
    br label %L125
    %r84 = load i32, ptr @pos
    %r85 = load i32, ptr %r84
    %r88 = add i32 %r85,%r86
    %r89 = load i32, ptr @pos
    store i32 %r88, ptr %r89
    br label %L125
L124:  
L125:  
L126:  
    br label %L118
L127:  
L128:  
L129:  
    %r74 = load i32, ptr @pos
    %r75 = load i32, ptr %r74
    %r78 = add i32 %r75,%r76
    %r79 = load i32, ptr @pos
    store i32 %r78, ptr %r79
    br label %L116
    %r62 = load i32, ptr %r61
    %r65 = icmp eq i32 %r62,%r63
    br i1 %r65, label %L132, label %L133
    %r66 = load i32, ptr @pos
    %r67 = load i32, ptr %r66
    %r70 = add i32 %r67,%r68
    %r71 = load i32, ptr @pos
    store i32 1, ptr %r71
    %r64 = call i32 @skip_space(i32 %r62,i32 %r63)
    %r65 = load i32, ptr @pos
    %r66 = load i32, ptr %r65
    %r65 = icmp slt i32 %r66,%r63
    br i1 %r65, label %L135, label %L136
    %r66 = load i32, ptr @pos
    %r67 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r66
    %r68 = load i32, ptr %r67
    %r71 = icmp eq i32 %r68,%r69
    br i1 %r71, label %L138, label %L139
    %r72 = load i32, ptr @pos
    %r73 = load i32, ptr %r72
    %r76 = add i32 %r73,%r74
    %r77 = load i32, ptr @pos
    store i32 1, ptr %r77
    ret i32 1
    br label %L140
L130:  
L132:  
    br label %L128
L133:  
L134:  
L135:  
    br label %L116
L136:  
L138:  
    %r64 = call i32 @detect_item(i32 %r79,i32 %r62,i32 %r63)
    %r65 = load i32, ptr %r64
    %r68 = icmp eq i32 %r65,%r66
    br i1 %r68, label %L141, label %L142
    ret i32 123
    br label %L143
L139:  
L141:  
    br label %L137
L142:  
L144:  
    %r64 = call i32 @skip_space(i32 %r62,i32 %r63)
    br label %L144
    %r65 = load i32, ptr @pos
    %r66 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r65
    %r70 = icmp eq i32 %r66,%r68
    br i1 %r70, label %L145, label %L146
    %r71 = load i32, ptr @pos
    %r72 = load i32, ptr %r71
    %r75 = add i32 %r72,%r73
    %r76 = load i32, ptr @pos
    store i32 1, ptr %r76
    %r64 = call i32 @skip_space(i32 %r62,i32 %r63)
    %r64 = call i32 @detect_item(i32 %r65,i32 %r62,i32 %r63)
    %r65 = load i32, ptr %r64
    %r68 = icmp eq i32 %r65,%r66
    br i1 %r68, label %L147, label %L148
    ret i32 123
    br label %L149
L145:  
L146:  
L147:  
    %r64 = call i32 @skip_space(i32 %r62,i32 %r63)
    %r65 = load i32, ptr @pos
    %r66 = load i32, ptr %r65
    %r65 = icmp sge i32 %r66,%r63
    br i1 %r65, label %L150, label %L151
    ret i32 0
    br label %L152
L148:  
L150:  
    %r64 = call i32 @skip_space(i32 %r62,i32 %r63)
    br label %L145
L151:  
L153:  
    %r67 = load i32, ptr @pos
    %r68 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r67
    %r72 = icmp ne i32 %r68,%r70
    br i1 %r72, label %L153, label %L154
    ret i32 0
    br label %L155
L154:  
L156:  
    %r74 = load i32, ptr @pos
    %r75 = load i32, ptr %r74
    %r78 = add i32 %r75,%r76
    %r79 = load i32, ptr @pos
    store i32 1, ptr %r79
    br label %L134
    %r62 = load i32, ptr %r61
    %r65 = icmp eq i32 %r62,%r63
    br i1 %r65, label %L156, label %L157
    %r66 = load i32, ptr @pos
    %r67 = load i32, ptr %r66
    %r70 = add i32 %r67,%r68
    %r71 = load i32, ptr @pos
    store i32 1, ptr %r71
    %r64 = call i32 @skip_space(i32 %r62,i32 %r63)
    %r65 = load i32, ptr @pos
    %r66 = load i32, ptr %r65
    %r65 = icmp slt i32 %r66,%r63
    br i1 %r65, label %L159, label %L160
    %r66 = load i32, ptr @pos
    %r67 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r66
    %r68 = load i32, ptr %r67
    %r71 = icmp eq i32 %r68,%r69
    br i1 %r71, label %L162, label %L163
    %r72 = load i32, ptr @pos
    %r73 = load i32, ptr %r72
    %r76 = add i32 %r73,%r74
    %r77 = load i32, ptr @pos
    store i32 1, ptr %r77
    ret i32 1
    br label %L164
L157:  
L158:  
L159:  
    br label %L134
L160:  
L162:  
    %r64 = call i32 @detect_item(i32 %r79,i32 %r62,i32 %r63)
    %r65 = load i32, ptr %r64
    %r68 = icmp eq i32 %r65,%r66
    br i1 %r68, label %L165, label %L166
    ret i32 123
    br label %L167
L163:  
L165:  
    br label %L161
L166:  
L168:  
    %r64 = call i32 @skip_space(i32 %r62,i32 %r63)
    %r65 = load i32, ptr @pos
    %r66 = load i32, ptr %r65
    %r65 = icmp sge i32 %r66,%r63
    br i1 %r65, label %L168, label %L169
    ret i32 0
    br label %L170
L169:  
L171:  
    %r67 = load i32, ptr @pos
    %r68 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r67
    %r72 = icmp ne i32 %r68,%r70
    br i1 %r72, label %L171, label %L172
    ret i32 0
    br label %L173
L172:  
L174:  
    %r74 = load i32, ptr @pos
    %r75 = load i32, ptr %r74
    %r78 = add i32 %r75,%r76
    %r79 = load i32, ptr @pos
    store i32 1, ptr %r79
    %r64 = call i32 @skip_space(i32 %r62,i32 %r63)
    %r64 = call i32 @detect_item(i32 %r65,i32 %r62,i32 %r63)
    %r65 = load i32, ptr %r64
    %r68 = icmp eq i32 %r65,%r66
    br i1 %r68, label %L174, label %L175
    ret i32 123
    br label %L176
L175:  
L177:  
    %r64 = call i32 @skip_space(i32 %r62,i32 %r63)
    br label %L177
    %r65 = load i32, ptr @pos
    %r66 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r65
    %r70 = icmp eq i32 %r66,%r68
    br i1 %r70, label %L178, label %L179
    %r71 = load i32, ptr @pos
    %r72 = load i32, ptr %r71
    %r75 = add i32 %r72,%r73
    %r76 = load i32, ptr @pos
    store i32 1, ptr %r76
    %r64 = call i32 @skip_space(i32 %r62,i32 %r63)
    %r64 = call i32 @detect_item(i32 %r65,i32 %r62,i32 %r63)
    %r65 = load i32, ptr %r64
    %r68 = icmp eq i32 %r65,%r66
    br i1 %r68, label %L180, label %L181
    ret i32 123
    br label %L182
L178:  
L179:  
L180:  
    %r64 = call i32 @skip_space(i32 %r62,i32 %r63)
    %r65 = load i32, ptr @pos
    %r66 = load i32, ptr %r65
    %r65 = icmp sge i32 %r66,%r63
    br i1 %r65, label %L192, label %L193
    ret i32 0
    br label %L194
    %r67 = load i32, ptr @pos
    %r68 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r67
    %r72 = icmp ne i32 %r68,%r70
    br i1 %r72, label %L195, label %L196
    ret i32 0
    br label %L197
L181:  
L183:  
    %r64 = call i32 @skip_space(i32 %r62,i32 %r63)
    %r65 = load i32, ptr @pos
    %r66 = load i32, ptr %r65
    %r65 = icmp sge i32 %r66,%r63
    br i1 %r65, label %L183, label %L184
    ret i32 0
    br label %L185
L184:  
L186:  
    %r67 = load i32, ptr @pos
    %r68 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r67
    %r72 = icmp ne i32 %r68,%r70
    br i1 %r72, label %L186, label %L187
    ret i32 0
    br label %L188
L187:  
L189:  
    %r74 = load i32, ptr @pos
    %r75 = load i32, ptr %r74
    %r78 = add i32 %r75,%r76
    %r79 = load i32, ptr @pos
    store i32 1, ptr %r79
    %r64 = call i32 @skip_space(i32 %r62,i32 %r63)
    %r64 = call i32 @detect_item(i32 %r65,i32 %r62,i32 %r63)
    %r65 = load i32, ptr %r64
    %r68 = icmp eq i32 %r65,%r66
    br i1 %r68, label %L189, label %L190
    ret i32 123
    br label %L191
L190:  
L192:  
    %r64 = call i32 @skip_space(i32 %r62,i32 %r63)
    br label %L178
L193:  
L194:  
L195:  
    %r66 = alloca [4 x i32]
    %r74 = load i32, ptr @pos
    %r75 = load i32, ptr %r74
    %r78 = add i32 %r75,%r76
    %r79 = load i32, ptr @pos
    store i32 1, ptr %r79
    br label %L158
    %r62 = load i32, ptr %r61
    %r65 = icmp eq i32 %r62,%r63
    br i1 %r65, label %L198, label %L199
    %r68 = getelementptr [4 x i32], ptr %r66, i32 0, i32 0
    store i32 116, ptr %r68
    %r70 = getelementptr [4 x i32], ptr %r66, i32 0, i32 1
    store i32 123, ptr %r70
    %r72 = getelementptr [4 x i32], ptr %r66, i32 0, i32 2
    store i32 117, ptr %r72
    %r74 = getelementptr [4 x i32], ptr %r66, i32 0, i32 3
    store i32 0, ptr %r74
    %r75 = load i32, ptr @pos
    %r76 = load i32, ptr %r75
    %r79 = add i32 %r76,%r77
    %r80 = load i32, ptr %r79
    %r65 = icmp sge i32 %r80,%r63
    br i1 %r65, label %L201, label %L202
    ret i32 0
    br label %L203
    %r67 = load i32, ptr @pos
    %r68 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r67
    %r71 = getelementptr [4 x i32], ptr %r66, i32 0, i32 %r70
    %r72 = load i32, ptr %r71
    %r73 = icmp ne i32 %r68,%r72
    br i1 %r73, label %L204, label %L205
    ret i32 0
    br label %L206
    %r75 = load i32, ptr @pos
    %r76 = load i32, ptr %r75
    %r79 = add i32 %r76,%r77
    %r80 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r79
    %r83 = getelementptr [4 x i32], ptr %r66, i32 0, i32 %r82
    %r84 = load i32, ptr %r83
    %r85 = icmp ne i32 %r80,%r84
    br i1 %r85, label %L207, label %L208
    ret i32 1
    br label %L209
    %r87 = load i32, ptr @pos
    %r88 = load i32, ptr %r87
    %r91 = add i32 %r88,%r89
    %r92 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r91
    %r93 = load float, ptr %r92
    %r95 = getelementptr [4 x i32], ptr %r66, i32 0, i32 %r94
    %r96 = load float, ptr %r95
    %r97 = icmp ne i32 %r93,%r96
    br i1 %r97, label %L210, label %L211
    ret i32 0
    br label %L212
    %r99 = load i32, ptr @pos
    %r100 = load i32, ptr %r99
    %r103 = add i32 %r100,%r101
    %r104 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r103
    %r105 = load float, ptr %r104
    %r107 = getelementptr [4 x i32], ptr %r66, i32 0, i32 %r106
    %r108 = load float, ptr %r107
    %r109 = icmp ne i32 %r105,%r108
    br i1 %r109, label %L213, label %L214
    ret i32 0
    br label %L215
L196:  
L198:  
    br label %L194
L199:  
L200:  
L201:  
    br label %L158
L202:  
L203:  
L204:  
    %r66 = alloca [5 x i32]
    %r111 = load i32, ptr @pos
    %r112 = load i32, ptr %r111
    %r115 = add i32 %r112,%r113
    %r116 = load i32, ptr @pos
    store i32 %r115, ptr %r116
    br label %L200
    %r62 = load i32, ptr %r61
    %r65 = icmp eq i32 %r62,%r63
    br i1 %r65, label %L216, label %L217
    %r68 = getelementptr [5 x i32], ptr %r66, i32 0, i32 0
    store i32 102, ptr %r68
    %r70 = getelementptr [5 x i32], ptr %r66, i32 0, i32 1
    store i32 123, ptr %r70
    %r72 = getelementptr [5 x i32], ptr %r66, i32 0, i32 2
    store i32 117, ptr %r72
    %r74 = getelementptr [5 x i32], ptr %r66, i32 0, i32 3
    store i32 0, ptr %r74
    %r76 = getelementptr [5 x i32], ptr %r66, i32 0, i32 4
    store i32 101, ptr %r76
    %r77 = load i32, ptr @pos
    %r78 = load i32, ptr %r77
    %r81 = add i32 %r78,%r79
    %r65 = icmp sge i32 %r81,%r63
    br i1 %r65, label %L219, label %L220
    ret i32 0
    br label %L221
    %r67 = load i32, ptr @pos
    %r68 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r67
    %r71 = getelementptr [5 x i32], ptr %r66, i32 0, i32 %r70
    %r72 = load i32, ptr %r71
    %r73 = icmp ne i32 %r68,%r72
    br i1 %r73, label %L222, label %L223
    ret i32 0
    br label %L224
    %r75 = load i32, ptr @pos
    %r76 = load i32, ptr %r75
    %r79 = add i32 %r76,%r77
    %r80 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r79
    %r83 = getelementptr [5 x i32], ptr %r66, i32 0, i32 %r82
    %r84 = load i32, ptr %r83
    %r85 = icmp ne i32 %r80,%r84
    br i1 %r85, label %L225, label %L226
    ret i32 1
    br label %L227
    %r87 = load i32, ptr @pos
    %r88 = load i32, ptr %r87
    %r91 = add i32 %r88,%r89
    %r92 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r91
    %r93 = load float, ptr %r92
    %r95 = getelementptr [5 x i32], ptr %r66, i32 0, i32 %r94
    %r96 = load float, ptr %r95
    %r97 = icmp ne i32 %r93,%r96
    br i1 %r97, label %L228, label %L229
    ret i32 0
    br label %L230
    %r99 = load i32, ptr @pos
    %r100 = load i32, ptr %r99
    %r103 = add i32 %r100,%r101
    %r104 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r103
    %r105 = load float, ptr %r104
    %r107 = getelementptr [5 x i32], ptr %r66, i32 0, i32 %r106
    %r108 = load float, ptr %r107
    %r109 = icmp ne i32 %r105,%r108
    br i1 %r109, label %L231, label %L232
    ret i32 0
    br label %L233
    %r111 = load i32, ptr @pos
    %r112 = load i32, ptr %r111
    %r115 = add i32 %r112,%r113
    %r116 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r115
    %r117 = load i32, ptr %r116
    %r119 = getelementptr [5 x i32], ptr %r66, i32 0, i32 %r118
    %r120 = load float, ptr %r119
    %r121 = icmp ne i32 %r117,%r120
    br i1 %r121, label %L234, label %L235
    ret i32 0
    br label %L236
L205:  
L206:  
L207:  
    br label %L203
L208:  
L209:  
L210:  
    br label %L206
L211:  
L212:  
L213:  
    br label %L209
L214:  
L216:  
    br label %L212
L217:  
L218:  
L219:  
    br label %L200
L220:  
L221:  
L222:  
    %r66 = alloca [4 x i32]
    %r123 = load i32, ptr @pos
    %r124 = load i32, ptr %r123
    %r127 = add i32 %r124,%r125
    %r128 = load i32, ptr @pos
    store i32 %r127, ptr %r128
    br label %L218
    %r62 = load i32, ptr %r61
    %r65 = icmp eq i32 %r62,%r63
    br i1 %r65, label %L237, label %L238
    %r68 = getelementptr [4 x i32], ptr %r66, i32 0, i32 0
    store i32 110, ptr %r68
    %r70 = getelementptr [4 x i32], ptr %r66, i32 0, i32 1
    store i32 123, ptr %r70
    %r72 = getelementptr [4 x i32], ptr %r66, i32 0, i32 2
    store i32 117, ptr %r72
    %r74 = getelementptr [4 x i32], ptr %r66, i32 0, i32 3
    store i32 0, ptr %r74
    %r75 = load i32, ptr @pos
    %r76 = load i32, ptr %r75
    %r79 = add i32 %r76,%r77
    %r65 = icmp sge i32 %r79,%r63
    br i1 %r65, label %L240, label %L241
    ret i32 0
    br label %L242
    %r67 = load i32, ptr @pos
    %r68 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r67
    %r71 = getelementptr [4 x i32], ptr %r66, i32 0, i32 %r70
    %r72 = load i32, ptr %r71
    %r73 = icmp ne i32 %r68,%r72
    br i1 %r73, label %L243, label %L244
    ret i32 0
    br label %L245
    %r75 = load i32, ptr @pos
    %r76 = load i32, ptr %r75
    %r79 = add i32 %r76,%r77
    %r80 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r79
    %r83 = getelementptr [4 x i32], ptr %r66, i32 0, i32 %r82
    %r84 = load i32, ptr %r83
    %r85 = icmp ne i32 %r80,%r84
    br i1 %r85, label %L246, label %L247
    ret i32 1
    br label %L248
    %r87 = load i32, ptr @pos
    %r88 = load i32, ptr %r87
    %r91 = add i32 %r88,%r89
    %r92 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r91
    %r93 = load float, ptr %r92
    %r95 = getelementptr [4 x i32], ptr %r66, i32 0, i32 %r94
    %r96 = load float, ptr %r95
    %r97 = icmp ne i32 %r93,%r96
    br i1 %r97, label %L249, label %L250
    ret i32 0
    br label %L251
    %r99 = load i32, ptr @pos
    %r100 = load i32, ptr %r99
    %r103 = add i32 %r100,%r101
    %r104 = getelementptr [0 x i32], ptr %r62, i32 0, i32 %r103
    %r105 = load float, ptr %r104
    %r107 = getelementptr [4 x i32], ptr %r66, i32 0, i32 %r106
    %r108 = load float, ptr %r107
    %r109 = icmp ne i32 %r105,%r108
    br i1 %r109, label %L252, label %L253
    ret i32 0
    br label %L254
L223:  
L224:  
L225:  
    br label %L221
L226:  
L227:  
L228:  
    br label %L224
L229:  
L230:  
L231:  
    br label %L227
L232:  
L233:  
L234:  
    br label %L230
L235:  
L237:  
    br label %L233
L238:  
L239:  
L240:  
    br label %L218
L241:  
L242:  
L243:  
    %r111 = load i32, ptr @pos
    %r112 = load i32, ptr %r111
    %r115 = add i32 %r112,%r113
    %r116 = load i32, ptr @pos
    store i32 %r115, ptr %r116
    br label %L239
    ret i32 0
    br label %L239
L244:  
L245:  
L246:  
    br label %L242
L247:  
L248:  
L249:  
    br label %L245
L250:  
L251:  
L252:  
    br label %L248
L253:  
L255:  
    br label %L251
}
define float @skip_space(i32 %r0,i32 %r9)
{
L1:  
    br label %L6
    br i1 %r11, label %L7, label %L8
    %r12 = load i32, ptr @pos
    %r13 = load i32, ptr %r12
    %r11 = load i32, ptr %r10
    %r12 = icmp sge i32 %r13,%r11
    br i1 %r12, label %L9, label %L10
    br label %L8
    br label %L11
L7:  
L8:  
L9:  
L10:  
L12:  
    %r13 = load i32, ptr @pos
    %r14 = getelementptr [0 x i32], ptr %r9, i32 0, i32 %r13
    %r15 = load float, ptr %r14
    %r18 = icmp eq i32 %r15,%r16
    br i1 %r18, label %L12, label %L13
    %r19 = load i32, ptr @pos
    %r20 = load i32, ptr %r19
    %r23 = add i32 %r20,%r21
    %r24 = load i32, ptr @pos
    store i32 %r23, ptr %r24
    br label %L14
    %r25 = load i32, ptr @pos
    %r26 = getelementptr [0 x i32], ptr %r9, i32 0, i32 %r25
    %r27 = load float, ptr %r26
    %r30 = icmp eq i32 %r27,%r28
    br i1 %r30, label %L15, label %L16
    %r31 = load i32, ptr @pos
    %r32 = load i32, ptr %r31
    %r35 = add i32 %r32,%r33
    %r36 = load i32, ptr @pos
    store i32 %r35, ptr %r36
    br label %L17
    %r37 = load i32, ptr @pos
    %r38 = getelementptr [0 x i32], ptr %r9, i32 0, i32 %r37
    %r39 = load float, ptr %r38
    %r42 = icmp eq i32 %r39,%r40
    br i1 %r42, label %L18, label %L19
    %r43 = load i32, ptr @pos
    %r44 = load i32, ptr %r43
    %r47 = add i32 %r44,%r45
    %r48 = load i32, ptr @pos
    store i32 %r47, ptr %r48
    br label %L20
    %r49 = load i32, ptr @pos
    %r50 = getelementptr [0 x i32], ptr %r9, i32 0, i32 %r49
    %r51 = load float, ptr %r50
    %r54 = icmp eq i32 %r51,%r52
    br i1 %r54, label %L21, label %L22
    %r55 = load i32, ptr @pos
    %r56 = load i32, ptr %r55
    %r59 = add i32 %r56,%r57
    %r60 = load i32, ptr @pos
    store i32 %r59, ptr %r60
    br label %L23
    br label %L8
    br label %L23
L13:  
L14:  
L15:  
    br label %L7
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
}
define i32 @main()
{
L1:  
    %r121 = alloca i32
    %r119 = alloca i32
    %r120 = call i32 @getch()
    store i32 %r120, ptr %r119
    store i32 0, ptr %r121
    br label %L255
    %r120 = load i32, ptr %r119
    %r123 = icmp ne i32 %r120,%r121
    br i1 %r123, label %L256, label %L257
    %r122 = getelementptr [50000000 x i32], ptr @buffer, i32 0, i32 %r121
    store i32 %r119, ptr %r122
    %r125 = add i32 %r121,%r123
    store i32 5, ptr %r121
    %r122 = call i32 @getch()
    store i32 0, ptr %r119
    br label %L256
L256:  
L257:  
L258:  
    %r123 = alloca i32
    %r120 = load i32, ptr @buffer
    %r122 = call i32 @skip_space(i32 %r120,i32 %r121)
    %r125 = load i32, ptr @buffer
    %r122 = call i32 @detect_item(i32 %r124,i32 %r125,i32 %r121)
    store i32 0, ptr %r123
    %r123 = load i32, ptr @buffer
    %r122 = call i32 @skip_space(i32 %r123,i32 %r121)
    %r124 = load i32, ptr %r123
    %r127 = icmp ne i32 %r124,%r125
    br i1 %r127, label %L258, label %L259
    %r129 = call i32 @putch(i32 %r128)
    %r131 = call i32 @putch(i32 %r130)
    %r133 = call i32 @putch(i32 %r132)
    ret i32 0
    br label %L260
    %r136 = call i32 @putch(i32 %r135)
    %r138 = call i32 @putch(i32 %r137)
    %r140 = call i32 @putch(i32 %r139)
    %r142 = call i32 @putch(i32 %r141)
    %r144 = call i32 @putch(i32 %r143)
    %r146 = call i32 @putch(i32 %r145)
    %r148 = call i32 @putch(i32 %r147)
    ret i32 1
    br label %L260
L259:  
L260:  
L261:  
}
