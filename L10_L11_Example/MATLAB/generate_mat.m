function generate_mat(name, x)

HEADER_STR = {
   ['/* MATLAB GENERATED HEADER FILE: ' name '_mat.h */']
   ['#ifndef INC_' upper(name) '_MAT_H_']
   ['#define INC_' upper(name) '_MAT_H_']
    ''
    '#include "arm_math.h"'
    ''
   ['#define ' upper(name) '_ROWS ' num2str(size(x,1))]
   ['#define ' upper(name) '_COLS ' num2str(size(x,2))]
   ['extern float32_t* ' upper(name) '_DATA;']
   ['extern arm_matrix_instance_f32 ' name ';']
    ''
   ['#endif /* INC_' upper(name) '_MAT_H_ */']
};

fileID = fopen([name '_mat.h'],'w');
for i = 1 : length(HEADER_STR)
    fprintf(fileID,'%s\n', HEADER_STR{i});
end
fclose(fileID);

SOURCE_STR = {
   ['/* MATLAB GENERATED SOURCE FILE: ' name '_mat.c */']
   ['#include "' name '_mat.h"']
   ['uint32_t ' upper(name) '_DATA_UINT[' upper(name) '_ROWS*' upper(name) '_COLS] = ']
    '{'
   ['  #include "' name '.csv"']
    '};'
   ['float32_t* ' upper(name) '_DATA = (float32_t*)' upper(name) '_DATA_UINT;']   
   ['arm_matrix_instance_f32 ' name ';']
};

fileID = fopen([name '_mat.c'],'w');
for i = 1 : length(SOURCE_STR)
    fprintf(fileID,'%s\n', SOURCE_STR{i});
end
fclose(fileID);

x = x';
x = x(:);

vec2csvfile([name '.csv'], x);
