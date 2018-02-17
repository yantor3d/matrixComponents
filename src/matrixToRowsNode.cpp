/**
    Copyright (c) 2018 Ryan Porter
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

/**
extractMatrixRows node
This node returns the values of each row of the matrix.

    matrix (m) matrix

    output (o) compound
        output00 (o00) double
        output01 (o01) double
        output02 (o02) double
        output03 (o03) double

        output10 (o10) double
        output11 (o11) double
        output12 (o12) double
        output13 (o13) double

        output20 (o20) double
        output21 (o21) double
        output22 (o22) double
        output23 (o23) double

        output30 (o30) double
        output31 (o31) double
        output32 (o32) double
        output33 (o33) double
*/

#include "matrixToRowsNode.h"

#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnData.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnNumericData.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MMatrix.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>

MObject MatrixToRows::matrixAttr;

MObject MatrixToRows::outAttr;
    MObject MatrixToRows::out00Attr;
    MObject MatrixToRows::out01Attr;
    MObject MatrixToRows::out02Attr;
    MObject MatrixToRows::out03Attr;

    MObject MatrixToRows::out10Attr;
    MObject MatrixToRows::out11Attr;
    MObject MatrixToRows::out12Attr;
    MObject MatrixToRows::out13Attr;

    MObject MatrixToRows::out20Attr;
    MObject MatrixToRows::out21Attr;
    MObject MatrixToRows::out22Attr;
    MObject MatrixToRows::out23Attr;

    MObject MatrixToRows::out30Attr;
    MObject MatrixToRows::out31Attr;
    MObject MatrixToRows::out32Attr;
    MObject MatrixToRows::out33Attr;
    

void* MatrixToRows::creator()
{
    return new MatrixToRows();
}


MStatus MatrixToRows::initialize()
{
    MStatus status;

    MFnCompoundAttribute c;
    MFnMatrixAttribute m;
    MFnNumericAttribute n;

    matrixAttr = m.create("matrix", "m", MFnMatrixAttribute::Type::kDouble, &status);

    out00Attr = n.create("out00", "o00", MFnNumericData::kDouble, 1.0, &status);
    out01Attr = n.create("out01", "o01", MFnNumericData::kDouble, 1.0, &status);
    out02Attr = n.create("out02", "o02", MFnNumericData::kDouble, 1.0, &status);
    out03Attr = n.create("out03", "o03", MFnNumericData::kDouble, 1.0, &status);

    out10Attr = n.create("out10", "o10", MFnNumericData::kDouble, 1.0, &status);
    out11Attr = n.create("out11", "o11", MFnNumericData::kDouble, 1.0, &status);
    out12Attr = n.create("out12", "o12", MFnNumericData::kDouble, 1.0, &status);
    out13Attr = n.create("out13", "o13", MFnNumericData::kDouble, 1.0, &status);

    out20Attr = n.create("out20", "o20", MFnNumericData::kDouble, 1.0, &status);
    out21Attr = n.create("out21", "o21", MFnNumericData::kDouble, 1.0, &status);
    out22Attr = n.create("out22", "o22", MFnNumericData::kDouble, 1.0, &status);
    out23Attr = n.create("out23", "o23", MFnNumericData::kDouble, 1.0, &status);

    out30Attr = n.create("out30", "o30", MFnNumericData::kDouble, 1.0, &status);
    out31Attr = n.create("out31", "o31", MFnNumericData::kDouble, 1.0, &status);
    out32Attr = n.create("out32", "o32", MFnNumericData::kDouble, 1.0, &status);
    out33Attr = n.create("out33", "o33", MFnNumericData::kDouble, 1.0, &status);

    outAttr =   c.create("output", "o");
    c.addChild(out00Attr);
    c.addChild(out01Attr);
    c.addChild(out02Attr);
    c.addChild(out03Attr);

    c.addChild(out10Attr);
    c.addChild(out11Attr);
    c.addChild(out12Attr);
    c.addChild(out13Attr);

    c.addChild(out20Attr);
    c.addChild(out21Attr);
    c.addChild(out22Attr);
    c.addChild(out23Attr);

    c.addChild(out30Attr);
    c.addChild(out31Attr);
    c.addChild(out32Attr);
    c.addChild(out33Attr);

    c.setWritable(false);
    c.setStorable(false);

    addAttribute(matrixAttr);
    addAttribute(outAttr);

    attributeAffects(matrixAttr, outAttr);

    return status;
}


MStatus MatrixToRows::compute(const MPlug& plug, MDataBlock& data)
{
    MStatus status;

    if (plug == outAttr || plug.parent() == outAttr)
    {
        MMatrix mat = data.inputValue(matrixAttr).asMatrix();

        extractRow(data, mat, 0, 0, out00Attr);
        extractRow(data, mat, 0, 1, out01Attr);
        extractRow(data, mat, 0, 2, out02Attr);
        extractRow(data, mat, 0, 3, out03Attr);

        extractRow(data, mat, 1, 0, out10Attr);
        extractRow(data, mat, 1, 1, out11Attr);
        extractRow(data, mat, 1, 2, out12Attr);
        extractRow(data, mat, 1, 3, out13Attr);

        extractRow(data, mat, 2, 0, out20Attr);
        extractRow(data, mat, 2, 1, out21Attr);
        extractRow(data, mat, 2, 2, out22Attr);
        extractRow(data, mat, 2, 3, out23Attr);

        extractRow(data, mat, 3, 0, out30Attr);
        extractRow(data, mat, 3, 1, out31Attr);
        extractRow(data, mat, 3, 2, out32Attr);
        extractRow(data, mat, 3, 3, out33Attr);

        data.setClean(outAttr);
    } else {
        status = MStatus::kUnknownParameter;
    }

    return status;   
}


MStatus MatrixToRows::extractRow(MDataBlock& data, const MMatrix &mat, unsigned int row, unsigned int col, MObject &attr)
{
    MStatus status;

    double value = mat(row, col);

    MDataHandle hnd = data.outputValue(attr);

    hnd.setDouble(value);
    hnd.setClean();

    return status; 
}