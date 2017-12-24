/*-------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Matrix2D.c
Purpose: Matrix2D class which includes implementation of Matrix operations
Language: C/C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24210 , x86  Windows
Project: CS529_ajaytanwar_2
Author: Ajay Singh Tanwar, ajay.tanwar, 60001317
Creation date: September 13th 2017
---------------------------------------------------------*/

#include "matrix2D.h"
#include <string.h>
#include <math.h>
#include "math-common.h"
/*
This function sets the matrix Result to the identity matrix
*/
namespace enginecore {

	namespace math {

		void Matrix2DIdentity(Matrix2D *pResult)
		{
			memset(pResult->matrix_, 0, sizeof(pResult->matrix_));

			pResult->matrix_[0][0] = 1.0f;
			pResult->matrix_[1][1] = 1.0f;
			pResult->matrix_[2][2] = 1.0f;

		}

		// ---------------------------------------------------------------------------

		/*
		This functions calculated the transpose matrix of Mtx and saves it in Result
		*/
		void Matrix2DTranspose(Matrix2D *pResult, Matrix2D *pMtx)
		{
			/*int r = 0, c = 0;*/


			float tempRes[3][3] = { { pMtx->matrix_[0][0],pMtx->matrix_[1][0] ,pMtx->matrix_[2][0] },
			{ pMtx->matrix_[0][1],pMtx->matrix_[1][1] ,pMtx->matrix_[2][1] },
			{ pMtx->matrix_[0][2],pMtx->matrix_[1][2] ,pMtx->matrix_[2][2] } };


			memcpy(pResult, &tempRes, sizeof(tempRes));

			/*for (; r < 3; r++) {

			c = 0;
			for (; c < 3; c++) {

			pResult->m[r][c] = temp[r][c];
			}
			}*/
		}

		// ---------------------------------------------------------------------------

		/*
		This function multiplies Mtx0 with Mtx1 and saves the result in Result
		Result = Mtx0*Mtx1
		*/
		void Matrix2DConcat(Matrix2D *pResult, Matrix2D *pMtx0, Matrix2D *pMtx1)
		{

			float tempRes[3][3];
			int r = 0, c = 0, i = 0;

			/*M1=
			1 2 3
			4 5 6
			7 8 9

			M2 =

			1 2 3
			4 5 6
			7 8 9
			*/


			tempRes[0][0] = pMtx0->matrix_[0][0] * pMtx1->matrix_[0][0] + pMtx0->matrix_[0][1] * pMtx1->matrix_[1][0] + pMtx0->matrix_[0][2] * pMtx1->matrix_[2][0];
			tempRes[0][1] = pMtx0->matrix_[0][0] * pMtx1->matrix_[0][1] + pMtx0->matrix_[0][1] * pMtx1->matrix_[1][1] + pMtx0->matrix_[0][2] * pMtx1->matrix_[2][1];
			tempRes[0][2] = pMtx0->matrix_[0][0] * pMtx1->matrix_[0][2] + pMtx0->matrix_[0][1] * pMtx1->matrix_[1][2] + pMtx0->matrix_[0][2] * pMtx1->matrix_[2][2];
								   												
			tempRes[1][0] = pMtx0->matrix_[1][0] * pMtx1->matrix_[0][0] + pMtx0->matrix_[1][1] * pMtx1->matrix_[1][0] + pMtx0->matrix_[1][2] * pMtx1->matrix_[2][0];
			tempRes[1][1] = pMtx0->matrix_[1][0] * pMtx1->matrix_[0][1] + pMtx0->matrix_[1][1] * pMtx1->matrix_[1][1] + pMtx0->matrix_[1][2] * pMtx1->matrix_[2][1];
			tempRes[1][2] = pMtx0->matrix_[1][0] * pMtx1->matrix_[0][2] + pMtx0->matrix_[1][1] * pMtx1->matrix_[1][2] + pMtx0->matrix_[1][2] * pMtx1->matrix_[2][2];
								   												
			tempRes[2][0] = pMtx0->matrix_[2][0] * pMtx1->matrix_[0][0] + pMtx0->matrix_[2][1] * pMtx1->matrix_[1][0] + pMtx0->matrix_[2][2] * pMtx1->matrix_[2][0];
			tempRes[2][1] = pMtx0->matrix_[2][0] * pMtx1->matrix_[0][1] + pMtx0->matrix_[2][1] * pMtx1->matrix_[1][1] + pMtx0->matrix_[2][2] * pMtx1->matrix_[2][1];
			tempRes[2][2] = pMtx0->matrix_[2][0] * pMtx1->matrix_[0][2] + pMtx0->matrix_[2][1] * pMtx1->matrix_[1][2] + pMtx0->matrix_[2][2] * pMtx1->matrix_[2][2];

			/*
			*Calculates the multiplication for two matrix and store in temp
			*/
			/*for (r = 0; r < 3; r++)
			{
			c = 0;
			for (; c < 3; c++)
			{
			tempRes[r][c] = 0;
			i = 0;
			for (; i < 3; i++) {

			tempRes[r][c] += pMtx0->m[r][i] * pMtx1->m[i][c];
			}

			}
			}*/

			/*
			*copies from source to dest
			*/
			memcpy(pResult->matrix_, &tempRes, sizeof(tempRes));

			/* r = 0, c = 0;
			for (; r < 3; r++) {

			c = 0;
			for (; c < 3; c++) {

			pResult->m[r][c] = temp[r][c];
			}
			}*/
		}

		// ---------------------------------------------------------------------------

		/*
		This function creates a translation matrix from x & y and saves it in Result
		*/
		void Matrix2DTranslate(Matrix2D *pResult, float x, float y)
		{
			Matrix2DIdentity(pResult);
			pResult->matrix_[0][2] = x;
			pResult->matrix_[1][2] = y;
		}

		// ---------------------------------------------------------------------------

		/*
		This function creates a scaling matrix from x & y and saves it in Result
		*/
		void Matrix2DScale(Matrix2D *pResult, float x, float y)
		{
			Matrix2DIdentity(pResult);
			pResult->matrix_[0][0] *= x;
			pResult->matrix_[1][1] *= y;
		}

		// ---------------------------------------------------------------------------

		/*
		This matrix creates a rotation matrix from "Angle" whose value is in degree.
		Save the resultant matrix in Result
		*/
		void Matrix2DRotDeg(Matrix2D *pResult, float Angle)
		{

			/*while (Angle >= 360.0f) {

			Angle = Angle-360.0f;
			}*/

			//printf("..angle :%.f", Angle);

			float rad = (float)(Angle *(MATH_PI / 180.0f));

			Matrix2DRotRad(pResult, rad);
			//printf("this is the angle :%.2f \n", Angle);

		}

		// ---------------------------------------------------------------------------

		/*
		This matrix creates a rotation matrix from "Angle" whose value is in radian.
		Save the resultant matrix in Result
		*/
		void Matrix2DRotRad(Matrix2D *pResult, float Angle)
		{

			Matrix2DIdentity(pResult);

			pResult->matrix_[0][0] = (float)cos(Angle);
			pResult->matrix_[0][1] = (float)-sin(Angle);
			pResult->matrix_[1][0] = (float)sin(Angle);
			pResult->matrix_[1][1] = (float)cos(Angle);

		}

		// ---------------------------------------------------------------------------

		/*
		This function multiplies the matrix Mtx with the vector Vec and saves the result in Result
		Result = Mtx * Vec
		*/
		void Matrix2DMultVec(Vector2D *pResult, Matrix2D *pMtx, Vector2D *pVec)
		{
			float _x = pVec->x_;
			float _y = pVec->y_;

			pResult->x_ = pMtx->matrix_[0][0] * _x + pMtx->matrix_[0][1] * _y + pMtx->matrix_[0][2];
			pResult->y_ = pMtx->matrix_[1][0] * _x + pMtx->matrix_[1][1] * _y + pMtx->matrix_[1][2];
		}

		// ---------------------------------------------------------------------------


	}
}
