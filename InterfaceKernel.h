//
// Created by afshaazi on 8/2/25.
//

#ifndef INTERFACEKERNEL_H
#define INTERFACEKERNEL_H
#include "Matrix.h"
#include "luxyd-ai-ioctl.h"

Matrix*         multiply_matrix_data(Matrix* _operand1, Matrix* _operand2);
matrix_info*    convert_operation_to_matrix_info(const Operation* _operation);

int             test_luxyd(const Operation* _operation);

#endif //INTERFACEKERNEL_H
