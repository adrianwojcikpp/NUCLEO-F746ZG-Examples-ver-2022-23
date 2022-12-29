%% Matrix multiplication unit test

%%% File info 
%
% ************************************************************************
%
%  @file     unit_test_mat_mult.m
%  @author   Adrian Wojcik
%  @version  2.0
%  @date     15-Dec-2020 08:55:55
%  @brief    Generates source, header and data (.csv) files for matrix
%            multiplication unit test
%
% ************************************************************************
%
close all; clc;
clear A x y
%% Matrix multiplication

A = single(rand(3,3));
B = single(rand(3,1));
C_REF = A*B;

disp("LHS ARGUMENT (MATRIX)");
disp(A);

disp("RHS ARGUMENT (COLUMN VECTOR)");
disp(B);

disp("REFERENCE RESULT:");
disp(C_REF);

%% Export files
generate_mat('A', A);
generate_mat('B', B);
generate_mat('C', zeros(size(C_REF)));
generate_mat('C_REF', C_REF);

