define i32 @main()
{
L1:  
    %r377 = alloca i32
    %r372 = alloca i32
    %r367 = alloca i32
    %r362 = alloca i32
    %r357 = alloca i32
    %r352 = alloca i32
    %r347 = alloca i32
    %r342 = alloca i32
    %r337 = alloca i32
    %r332 = alloca i32
    %r327 = alloca i32
    %r322 = alloca i32
    %r317 = alloca i32
    %r312 = alloca i32
    %r307 = alloca i32
    %r302 = alloca i32
    %r297 = alloca i32
    %r292 = alloca i32
    %r288 = load i32, ptr %r287
    %r291 = icmp slt i32 %r288,%r289
    br i1 %r291, label %L1, label %L2
    store i32 0, ptr %r292
    br label %L3
    %r293 = load i32, ptr %r292
    %r296 = icmp slt i32 %r293,%r294
    br i1 %r296, label %L4, label %L5
    store i32 0, ptr %r297
    br label %L6
    %r298 = load i32, ptr %r297
    %r301 = icmp slt i32 %r298,%r299
    br i1 %r301, label %L7, label %L8
    store i32 0, ptr %r302
    br label %L9
    %r303 = load i32, ptr %r302
    %r306 = icmp slt i32 %r303,%r304
    br i1 %r306, label %L10, label %L11
    store i32 0, ptr %r307
    br label %L12
    %r308 = load i32, ptr %r307
    %r311 = icmp slt i32 %r308,%r309
    br i1 %r311, label %L13, label %L14
    store i32 0, ptr %r312
    br label %L15
    %r313 = load i32, ptr %r312
    %r316 = icmp slt i32 %r313,%r314
    br i1 %r316, label %L16, label %L17
    store i32 0, ptr %r317
    br label %L18
    %r318 = load i32, ptr %r317
    %r321 = icmp slt i32 %r318,%r319
    br i1 %r321, label %L19, label %L20
    store i32 0, ptr %r322
    br label %L21
    %r323 = load i32, ptr %r322
    %r326 = icmp slt i32 %r323,%r324
    br i1 %r326, label %L22, label %L23
    store i32 0, ptr %r327
    br label %L24
    %r328 = load i32, ptr %r327
    %r331 = icmp slt i32 %r328,%r329
    br i1 %r331, label %L25, label %L26
    store i32 0, ptr %r332
    br label %L27
    %r333 = load i32, ptr %r332
    %r336 = icmp slt i32 %r333,%r334
    br i1 %r336, label %L28, label %L29
    store i32 0, ptr %r337
    br label %L30
    %r338 = load i32, ptr %r337
    %r341 = icmp slt i32 %r338,%r339
    br i1 %r341, label %L31, label %L32
    store i32 0, ptr %r342
    br label %L33
    %r343 = load i32, ptr %r342
    %r346 = icmp slt i32 %r343,%r344
    br i1 %r346, label %L34, label %L35
    store i32 0, ptr %r347
    br label %L36
    %r348 = load i32, ptr %r347
    %r351 = icmp slt i32 %r348,%r349
    br i1 %r351, label %L37, label %L38
    store i32 0, ptr %r352
    br label %L39
    %r353 = load i32, ptr %r352
    %r356 = icmp slt i32 %r353,%r354
    br i1 %r356, label %L40, label %L41
    store i32 0, ptr %r357
    br label %L42
    %r358 = load i32, ptr %r357
    %r361 = icmp slt i32 %r358,%r359
    br i1 %r361, label %L43, label %L44
    store i32 0, ptr %r362
    br label %L45
    %r363 = load i32, ptr %r362
    %r366 = icmp slt i32 %r363,%r364
    br i1 %r366, label %L46, label %L47
    store i32 0, ptr %r367
    br label %L48
    %r368 = load i32, ptr %r367
    %r371 = icmp slt i32 %r368,%r369
    br i1 %r371, label %L49, label %L50
    store i32 0, ptr %r372
    br label %L51
    %r373 = load i32, ptr %r372
    %r376 = icmp slt i32 %r373,%r374
    br i1 %r376, label %L52, label %L53
    store i32 0, ptr %r377
    br label %L54
    %r378 = load i32, ptr %r377
    %r381 = icmp slt i32 %r378,%r379
    br i1 %r381, label %L55, label %L56
    %r378 = getelementptr [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x i32]]]]]]]]]]]]]]]]]]], ptr %r282, i32 0, i32 %r287, i32 %r292, i32 %r297, i32 %r302, i32 %r307, i32 %r312, i32 %r317, i32 %r322, i32 %r327, i32 %r332, i32 %r337, i32 %r342, i32 %r347, i32 %r352, i32 %r357, i32 %r362, i32 %r367, i32 %r372, i32 %r377
    store i32 %r285, ptr %r378
    %r286 = load i32, ptr %r285
    %r289 = add i32 %r286,%r287
    store i32 2, ptr %r285
    %r378 = load i32, ptr %r377
    %r381 = add i32 %r378,%r379
    store i32 %r381, ptr %r377
    br label %L55
L2:  
L3:  
    %r306 = getelementptr [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x i32]]]]]]]]]]]]]]]]]]], ptr %r282, i32 0, i32 %r288, i32 %r289, i32 %r290, i32 %r291, i32 %r292, i32 %r293, i32 %r294, i32 %r295, i32 %r296, i32 %r297, i32 %r298, i32 %r299, i32 %r300, i32 %r301, i32 %r302, i32 %r303, i32 %r304, i32 %r305
    %r324 = getelementptr [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x i32]]]]]]]]]]]]]]]]]]], ptr %r282, i32 0, i32 %r307, i32 %r308, i32 %r309, i32 %r310, i32 %r311, i32 %r312, i32 %r313, i32 %r314, i32 %r315, i32 %r316, i32 %r317, i32 %r318, i32 %r319, i32 %r320, i32 %r321, i32 %r322, i32 %r323
    %r341 = getelementptr [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x i32]]]]]]]]]]]]]]]]]]], ptr %r282, i32 0, i32 %r325, i32 %r326, i32 %r327, i32 %r328, i32 %r329, i32 %r330, i32 %r331, i32 %r332, i32 %r333, i32 %r334, i32 %r335, i32 %r336, i32 %r337, i32 %r338, i32 %r339, i32 %r340
    %r357 = getelementptr [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x i32]]]]]]]]]]]]]]]]]]], ptr %r282, i32 0, i32 %r342, i32 %r343, i32 %r344, i32 %r345, i32 %r346, i32 %r347, i32 %r348, i32 %r349, i32 %r350, i32 %r351, i32 %r352, i32 %r353, i32 %r354, i32 %r355, i32 %r356
    %r372 = getelementptr [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x i32]]]]]]]]]]]]]]]]]]], ptr %r282, i32 0, i32 %r358, i32 %r359, i32 %r360, i32 %r361, i32 %r362, i32 %r363, i32 %r364, i32 %r365, i32 %r366, i32 %r367, i32 %r368, i32 %r369, i32 %r370, i32 %r371
    %r386 = getelementptr [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x i32]]]]]]]]]]]]]]]]]]], ptr %r282, i32 0, i32 %r373, i32 %r374, i32 %r375, i32 %r376, i32 %r377, i32 %r378, i32 %r379, i32 %r380, i32 %r381, i32 %r382, i32 %r383, i32 %r384, i32 %r385
    %r399 = getelementptr [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x i32]]]]]]]]]]]]]]]]]]], ptr %r282, i32 0, i32 %r387, i32 %r388, i32 %r389, i32 %r390, i32 %r391, i32 %r392, i32 %r393, i32 %r394, i32 %r395, i32 %r396, i32 %r397, i32 %r398
    %r411 = getelementptr [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x i32]]]]]]]]]]]]]]]]]]], ptr %r282, i32 0, i32 %r400, i32 %r401, i32 %r402, i32 %r403, i32 %r404, i32 %r405, i32 %r406, i32 %r407, i32 %r408, i32 %r409, i32 %r410
    %r422 = getelementptr [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x i32]]]]]]]]]]]]]]]]]]], ptr %r282, i32 0, i32 %r412, i32 %r413, i32 %r414, i32 %r415, i32 %r416, i32 %r417, i32 %r418, i32 %r419, i32 %r420, i32 %r421
    %r432 = getelementptr [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x i32]]]]]]]]]]]]]]]]]]], ptr %r282, i32 0, i32 %r423, i32 %r424, i32 %r425, i32 %r426, i32 %r427, i32 %r428, i32 %r429, i32 %r430, i32 %r431
    %r441 = getelementptr [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x i32]]]]]]]]]]]]]]]]]]], ptr %r282, i32 0, i32 %r433, i32 %r434, i32 %r435, i32 %r436, i32 %r437, i32 %r438, i32 %r439, i32 %r440
    %r449 = getelementptr [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x i32]]]]]]]]]]]]]]]]]]], ptr %r282, i32 0, i32 %r442, i32 %r443, i32 %r444, i32 %r445, i32 %r446, i32 %r447, i32 %r448
    %r456 = getelementptr [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x i32]]]]]]]]]]]]]]]]]]], ptr %r282, i32 0, i32 %r450, i32 %r451, i32 %r452, i32 %r453, i32 %r454, i32 %r455
    %r462 = getelementptr [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x i32]]]]]]]]]]]]]]]]]]], ptr %r282, i32 0, i32 %r457, i32 %r458, i32 %r459, i32 %r460, i32 %r461
    %r467 = getelementptr [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x i32]]]]]]]]]]]]]]]]]]], ptr %r282, i32 0, i32 %r463, i32 %r464, i32 %r465, i32 %r466
    %r471 = getelementptr [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x i32]]]]]]]]]]]]]]]]]]], ptr %r282, i32 0, i32 %r468, i32 %r469, i32 %r470
    %r474 = getelementptr [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x i32]]]]]]]]]]]]]]]]]]], ptr %r282, i32 0, i32 %r472, i32 %r473
    %r476 = getelementptr [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x [2 x i32]]]]]]]]]]]]]]]]]]], ptr %r282, i32 0, i32 %r475
    %r283 = call i32 @sum(float %r306,i32 %r324,float %r341,i32 %r357,i32 %r372,float %r386,float %r399,float %r411,float %r422,float %r432,float %r441,float %r449,float %r456,float %r462,float %r467,float %r471,float %r474,float %r476,i32 %r282)
    %r284 = call i32 @putint(float %r283)
    ret i32 0
L4:  
L5:  
L6:  
    %r291 = add i32 %r287,%r289
    store i32 %r291, ptr %r287
    br label %L1
L7:  
L8:  
L9:  
    %r293 = load i32, ptr %r292
    %r296 = add i32 %r293,%r294
    store i32 %r296, ptr %r292
    br label %L4
L10:  
L11:  
L12:  
    %r298 = load i32, ptr %r297
    %r301 = add i32 %r298,%r299
    store i32 %r301, ptr %r297
    br label %L7
L13:  
L14:  
L15:  
    %r303 = load i32, ptr %r302
    %r306 = add i32 %r303,%r304
    store i32 %r306, ptr %r302
    br label %L10
L16:  
L17:  
L18:  
    %r308 = load i32, ptr %r307
    %r311 = add i32 %r308,%r309
    store i32 %r311, ptr %r307
    br label %L13
L19:  
L20:  
L21:  
    %r313 = load i32, ptr %r312
    %r316 = add i32 %r313,%r314
    store i32 %r316, ptr %r312
    br label %L16
L22:  
L23:  
L24:  
    %r318 = load i32, ptr %r317
    %r321 = add i32 %r318,%r319
    store i32 %r321, ptr %r317
    br label %L19
L25:  
L26:  
L27:  
    %r323 = load i32, ptr %r322
    %r326 = add i32 %r323,%r324
    store i32 %r326, ptr %r322
    br label %L22
L28:  
L29:  
L30:  
    %r328 = load i32, ptr %r327
    %r331 = add i32 %r328,%r329
    store i32 %r331, ptr %r327
    br label %L25
L31:  
L32:  
L33:  
    %r333 = load i32, ptr %r332
    %r336 = add i32 %r333,%r334
    store i32 %r336, ptr %r332
    br label %L28
L34:  
L35:  
L36:  
    %r338 = load i32, ptr %r337
    %r341 = add i32 %r338,%r339
    store i32 %r341, ptr %r337
    br label %L31
L37:  
L38:  
L39:  
    %r343 = load i32, ptr %r342
    %r346 = add i32 %r343,%r344
    store i32 %r346, ptr %r342
    br label %L34
L40:  
L41:  
L42:  
    %r348 = load i32, ptr %r347
    %r351 = add i32 %r348,%r349
    store i32 %r351, ptr %r347
    br label %L37
L43:  
L44:  
L45:  
    %r353 = load i32, ptr %r352
    %r356 = add i32 %r353,%r354
    store i32 %r356, ptr %r352
    br label %L40
L46:  
L47:  
L48:  
    %r358 = load i32, ptr %r357
    %r361 = add i32 %r358,%r359
    store i32 %r361, ptr %r357
    br label %L43
L49:  
L50:  
L51:  
    %r363 = load i32, ptr %r362
    %r366 = add i32 %r363,%r364
    store i32 %r366, ptr %r362
    br label %L46
L52:  
L53:  
L54:  
    %r368 = load i32, ptr %r367
    %r371 = add i32 %r368,%r369
    store i32 %r371, ptr %r367
    br label %L49
L55:  
L56:  
L57:  
    %r373 = load i32, ptr %r372
    %r376 = add i32 %r373,%r374
    store i32 %r376, ptr %r372
    br label %L52
}
define i32 @sum(i32 %r0,i32 %r0,i32 %r2,i32 %r1,i32 %r4,i32 %r2,i32 %r6,i32 %r3,i32 %r8,i32 %r4,i32 %r10,i32 %r5,i32 %r12,i32 %r6,i32 %r14,i32 %r7,i32 %r16,i32 %r8,i32 %r18)
{
L1:  
    %r20 = getelementptr [0 x i32], ptr %r0, i32 0, i32 %r19
    %r21 = load float, ptr %r20
    %r24 = getelementptr [0 x i32], ptr %r1, i32 0, i32 %r22, i32 %r23
    %r25 = load float, ptr %r24
    %r26 = add i32 %r21,%r25
    %r27 = load float, ptr %r26
    %r31 = getelementptr [0 x i32], ptr %r2, i32 0, i32 %r28, i32 %r29, i32 %r30
    %r32 = load float, ptr %r31
    %r33 = add i32 %r27,%r32
    %r34 = load float, ptr %r33
    %r39 = getelementptr [0 x i32], ptr %r3, i32 0, i32 %r35, i32 %r36, i32 %r37, i32 %r38
    %r40 = load float, ptr %r39
    %r41 = add i32 %r34,%r40
    %r42 = load float, ptr %r41
    %r48 = getelementptr [0 x i32], ptr %r4, i32 0, i32 %r43, i32 %r44, i32 %r45, i32 %r46, i32 %r47
    %r49 = load float, ptr %r48
    %r50 = add i32 %r42,%r49
    %r51 = load float, ptr %r50
    %r58 = getelementptr [0 x i32], ptr %r5, i32 0, i32 %r52, i32 %r53, i32 %r54, i32 %r55, i32 %r56, i32 %r57
    %r59 = load float, ptr %r58
    %r60 = add i32 %r51,%r59
    %r61 = load float, ptr %r60
    %r69 = getelementptr [0 x i32], ptr %r6, i32 0, i32 %r62, i32 %r63, i32 %r64, i32 %r65, i32 %r66, i32 %r67, i32 %r68
    %r70 = load float, ptr %r69
    %r71 = add i32 %r61,%r70
    %r72 = load float, ptr %r71
    %r81 = getelementptr [0 x i32], ptr %r7, i32 0, i32 %r73, i32 %r74, i32 %r75, i32 %r76, i32 %r77, i32 %r78, i32 %r79, i32 %r80
    %r82 = load float, ptr %r81
    %r83 = add i32 %r72,%r82
    %r84 = load float, ptr %r83
    %r94 = getelementptr [0 x i32], ptr %r8, i32 0, i32 %r85, i32 %r86, i32 %r87, i32 %r88, i32 %r89, i32 %r90, i32 %r91, i32 %r92, i32 %r93
    %r95 = load float, ptr %r94
    %r96 = add i32 %r84,%r95
    %r97 = load float, ptr %r96
    %r108 = getelementptr [0 x i32], ptr %r9, i32 0, i32 %r98, i32 %r99, i32 %r100, i32 %r101, i32 %r102, i32 %r103, i32 %r104, i32 %r105, i32 %r106, i32 %r107
    %r109 = load float, ptr %r108
    %r110 = add i32 %r97,%r109
    %r111 = load float, ptr %r110
    %r123 = getelementptr [0 x i32], ptr %r10, i32 0, i32 %r112, i32 %r113, i32 %r114, i32 %r115, i32 %r116, i32 %r117, i32 %r118, i32 %r119, i32 %r120, i32 %r121, i32 %r122
    %r124 = load float, ptr %r123
    %r125 = add i32 %r111,%r124
    %r126 = load float, ptr %r125
    %r139 = getelementptr [0 x i32], ptr %r11, i32 0, i32 %r127, i32 %r128, i32 %r129, i32 %r130, i32 %r131, i32 %r132, i32 %r133, i32 %r134, i32 %r135, i32 %r136, i32 %r137, i32 %r138
    %r140 = load float, ptr %r139
    %r141 = add i32 %r126,%r140
    %r142 = load float, ptr %r141
    %r156 = getelementptr [0 x i32], ptr %r12, i32 0, i32 %r143, i32 %r144, i32 %r145, i32 %r146, i32 %r147, i32 %r148, i32 %r149, i32 %r150, i32 %r151, i32 %r152, i32 %r153, i32 %r154, i32 %r155
    %r157 = load float, ptr %r156
    %r158 = add i32 %r142,%r157
    %r159 = load float, ptr %r158
    %r174 = getelementptr [0 x i32], ptr %r13, i32 0, i32 %r160, i32 %r161, i32 %r162, i32 %r163, i32 %r164, i32 %r165, i32 %r166, i32 %r167, i32 %r168, i32 %r169, i32 %r170, i32 %r171, i32 %r172, i32 %r173
    %r175 = load float, ptr %r174
    %r176 = add i32 %r159,%r175
    %r177 = load float, ptr %r176
    %r193 = getelementptr [0 x i32], ptr %r14, i32 0, i32 %r178, i32 %r179, i32 %r180, i32 %r181, i32 %r182, i32 %r183, i32 %r184, i32 %r185, i32 %r186, i32 %r187, i32 %r188, i32 %r189, i32 %r190, i32 %r191, i32 %r192
    %r194 = load float, ptr %r193
    %r195 = add i32 %r177,%r194
    %r196 = load float, ptr %r195
    %r213 = getelementptr [0 x i32], ptr %r15, i32 0, i32 %r197, i32 %r198, i32 %r199, i32 %r200, i32 %r201, i32 %r202, i32 %r203, i32 %r204, i32 %r205, i32 %r206, i32 %r207, i32 %r208, i32 %r209, i32 %r210, i32 %r211, i32 %r212
    %r214 = load float, ptr %r213
    %r215 = add i32 %r196,%r214
    %r216 = load float, ptr %r215
    %r234 = getelementptr [0 x i32], ptr %r16, i32 0, i32 %r217, i32 %r218, i32 %r219, i32 %r220, i32 %r221, i32 %r222, i32 %r223, i32 %r224, i32 %r225, i32 %r226, i32 %r227, i32 %r228, i32 %r229, i32 %r230, i32 %r231, i32 %r232, i32 %r233
    %r235 = load float, ptr %r234
    %r236 = add i32 %r216,%r235
    %r237 = load float, ptr %r236
    %r256 = getelementptr [0 x i32], ptr %r17, i32 0, i32 %r238, i32 %r239, i32 %r240, i32 %r241, i32 %r242, i32 %r243, i32 %r244, i32 %r245, i32 %r246, i32 %r247, i32 %r248, i32 %r249, i32 %r250, i32 %r251, i32 %r252, i32 %r253, i32 %r254, i32 %r255
    %r257 = load float, ptr %r256
    %r258 = add i32 %r237,%r257
    %r259 = load float, ptr %r258
    %r279 = getelementptr [0 x i32], ptr %r18, i32 0, i32 %r260, i32 %r261, i32 %r262, i32 %r263, i32 %r264, i32 %r265, i32 %r266, i32 %r267, i32 %r268, i32 %r269, i32 %r270, i32 %r271, i32 %r272, i32 %r273, i32 %r274, i32 %r275, i32 %r276, i32 %r277, i32 %r278
    %r280 = load float, ptr %r279
    %r281 = add i32 %r259,%r280
    ret i32 %r281
}
