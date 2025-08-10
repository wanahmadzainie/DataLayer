//
// Created by afshaazi on 8/2/25.
//
#include "Matrix.h"
#include "common.h"
#include <assert.h>
#include <cstdio>
#include <stdlib.h>

#include "InterfaceKernel.h"
#include "MemTrack.h"
#include "luxyd-ai-ioctl.h"


#include "luxyd-ai-ioctl.h"
// interface layer function to send matrix data to kernel module for multiplication operation
// Inputs: Matrix operand1, Matrix operand2
// Returns: Matrix result
Matrix* multiply_matrix_data(Matrix* _operand1, Matrix* _operand2) {

    Matrix* result_matrix = nullptr;

    return result_matrix;
}

matrix_info* convert_operation_to_matrix_info(const Operation* _operation) {

    auto* this_matrix_info = (matrix_info*) calloc(1, sizeof(matrix_info));

    int result_row_size = 0;
    int result_col_size = 0;
    int operand1_operand2_common_dimension = 0;

    // null check
    if ( _operation == nullptr) {
        f_ree(this_matrix_info);
        return nullptr;
    }

    // sanity check
    if (_operation->operand1->rows != _operation->operand2->cols) {
        fprintf(stderr, "Incompatible operands detected in Operation ID:%d", _operation->operation_id);
        f_ree(this_matrix_info);
        return nullptr;
    }

    result_row_size = _operation->operand1->rows;
    result_col_size = _operation->operand2->cols;
    operand1_operand2_common_dimension = _operation->operand1->cols;

    // set the dimension info
    this_matrix_info->m = result_row_size;
    this_matrix_info->n = result_col_size;
    this_matrix_info->p = operand1_operand2_common_dimension;

    this_matrix_info->a_ptr = _operation->operand1->data->ushort_data;
    this_matrix_info->b_ptr = _operation->operand2->data->ushort_data;
    this_matrix_info->p_ptr = _operation->result->data->uint_data;

    return (matrix_info*) this_matrix_info;
}

#define test_dev_open_name	"luxyd-ai-test"

int test_luxyd(const Operation* _operation) {

    int             result = 0;
    unsigned int    max_row_size = 40;
    unsigned int    max_col_size = 40;
    unsigned int    matrix_count_per_operation = 3;
    unsigned int    temp_buffer_size = (max_row_size * max_col_size * matrix_count_per_operation) * sizeof(__u32) ;
    int             buffer_size = int(temp_buffer_size);

    matrix_info*    matrix_info = convert_operation_to_matrix_info(_operation);
    if (matrix_info != nullptr) {
        fprintf(stderr, "Operation to matrix info conversion failed\n");
        return RETURN_FAILURE;
    }

    int fd = luxyd_dev_open(test_dev_open_name);
    assert(fd > 0);

    void* buffer = luxyd_dev_init(fd, &buffer_size);

    result = luxyd_dev_matrix_load(fd, buffer, matrix_info);
    if (result > 0) {
        printf("Ok\n");
    }
    result = luxyd_dev_matrix_multiply(fd, buffer, matrix_info);
    if (result > 0) {
        printf("Ok\n");
    }

    result = luxyd_dev_close(fd, buffer, buffer_size);

    return result;

}