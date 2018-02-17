/**
    Copyright (c) 2018 Ryan Porter
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

/**
extractMatrixEulerRotation node
This node returns the orientation component of the input matrix as a euler rotation.

    matrix      (m) matrix
    rotateOrder (ro) enum

    output (o) doubleAngle3
        outputX (ox) doubleAngle
        outputY (oz) doubleAngle
        outputZ (oy) doubleAngle
*/

#include "matrixToEulerNode.h"

#include <maya/MAngle.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MEulerRotation.h>
#include <maya/MFnData.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MMatrix.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MString.h>
#include <maya/MTransformationMatrix.h>
#include <maya/MTypeId.h>


// Input Attributes
MObject MatrixToEulerRotation::matrixAttr;
MObject MatrixToEulerRotation::rotateOrderAttr;

// Output Attributes
MObject MatrixToEulerRotation::outputAttr;
    MObject MatrixToEulerRotation::outputXAttr;
    MObject MatrixToEulerRotation::outputYAttr;
    MObject MatrixToEulerRotation::outputZAttr;


void* MatrixToEulerRotation::creator()
{
    return new MatrixToEulerRotation();
}


MStatus MatrixToEulerRotation::initialize()
{
    MStatus status;

    MFnCompoundAttribute c;
    MFnEnumAttribute     e;
    MFnMatrixAttribute   m;
    MFnNumericAttribute  n;
    MFnUnitAttribute     u;

    matrixAttr = m.create("matrix", "m", MFnMatrixAttribute::Type::kDouble, &status);

    rotateOrderAttr = e.create("rotateOrder", "ro", 0, &status);
                      e.addField("XYZ", 0);
                      e.addField("YZX", 1);
                      e.addField("ZXY", 2);
                      e.addField("XZY", 3);
                      e.addField("YXZ", 4);
                      e.addField("ZYX", 5);

    outputXAttr = u.create("outputX", "ox", MFnUnitAttribute::Type::kAngle, 0.0, &status);
    outputYAttr = u.create("outputY", "oy", MFnUnitAttribute::Type::kAngle, 0.0, &status);
    outputZAttr = u.create("outputZ", "oz", MFnUnitAttribute::Type::kAngle, 0.0, &status);
    
    outputAttr = n.create("output", "o", outputXAttr, outputYAttr, outputZAttr, &status);
    n.setWritable(false);
    n.setStorable(false);

    addAttribute(matrixAttr);
    addAttribute(rotateOrderAttr);
    addAttribute(outputAttr);

    attributeAffects(matrixAttr, outputAttr);
    attributeAffects(rotateOrderAttr, outputAttr);

    return MStatus::kSuccess;
}


MStatus MatrixToEulerRotation::compute(const MPlug& plug, MDataBlock& data)
{
    MStatus status;

    if (plug == this->outputAttr || plug.parent() == this->outputAttr)
    {
        MEulerRotation::RotationOrder ord = (MEulerRotation::RotationOrder) data.inputValue(rotateOrderAttr).asShort();
        MMatrix mat = data.inputValue(matrixAttr).asMatrix();
        MTransformationMatrix t(mat);

        MEulerRotation e = t.eulerRotation().reorder(ord);

        MDataHandle outX = data.outputValue(outputXAttr);
        MDataHandle outY = data.outputValue(outputYAttr);
        MDataHandle outZ = data.outputValue(outputZAttr);

        MAngle x(e.x);
        MAngle y(e.y);
        MAngle z(e.z);

        outX.setMAngle(x);
        outY.setMAngle(y);
        outZ.setMAngle(z);

        outX.setClean();
        outY.setClean();
        outZ.setClean();

        data.setClean(outputAttr);
    } else {
        return MStatus::kUnknownParameter;
    }

    return MStatus::kSuccess; 
}