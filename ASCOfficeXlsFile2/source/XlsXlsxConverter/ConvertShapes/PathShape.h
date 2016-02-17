#pragma once

#include "GraphicsPath.h"
#include "FormulaShape.h"

namespace NSGuidesVML
{
	static std::wstring GetRulerVML(RulesType eRuler)
	{
		switch (eRuler)
		{
		case rtMoveTo:				{ return _T("m"); }
		case rtLineTo:				{ return _T("l"); }
		case rtCurveTo:				{ return _T("c"); }
		
		case rtClose:				{ return _T("x"); }
		case rtEnd:					{ return _T("e"); }
		
		case rtRMoveTo:				{ return _T("t"); }
		case rtRLineTo:				{ return _T("r"); }
		case rtRCurveTo:			{ return _T("v"); }
		
		case rtNoFill:				{ return _T("nf"); }
		case rtNoStroke:			{ return _T("ns"); }

		case rtAngleEllipseTo:		{ return _T("ae"); }
		case rtAngleEllipse:		{ return _T("al"); }
		
		case rtArc:					{ return _T("at"); }
		case rtArcTo:				{ return _T("ar"); }

		case rtClockwiseArcTo:		{ return _T("wa"); }
		case rtClockwiseArc:		{ return _T("wr"); }

		case rtEllipticalQuadrX:	{ return _T("qx"); }
		case rtEllipticalQuadrY:	{ return _T("qy"); }

		case rtQuadrBesier:			{ return _T("qb"); }
		default: break;
		};
		return _T("");
	}

	static RulesType GetRuler(const std::wstring& strName, bool& bRes)
	{
		bRes = true;
		if		(_T("moveTo")		== strName)	return rtOOXMLMoveTo;
		else if (_T("lnTo")			== strName)	return rtOOXMLLineTo;
		else if (_T("cubicBezTo")	== strName)	return rtOOXMLCubicBezTo;
		else if (_T("close")		== strName)	return rtOOXMLClose;
		else if (_T("end")			== strName)	return rtOOXMLEnd;
		else if (_T("arcTo")		== strName)	return rtOOXMLArcTo;
		else if (_T("quadBezTo")	== strName)	return rtOOXMLQuadBezTo;

		//bRes = true;
		else if	((_T("m") == strName) || (_T("M") == strName))		return rtMoveTo;
		else if ((_T("l") == strName) || (_T("L") == strName))		return rtLineTo;
		else if ((_T("c") == strName) || (_T("C") == strName))		return rtCurveTo;
		else if ((_T("x") == strName) || (_T("Z") == strName))		return rtClose;
		else if ((_T("e") == strName) || (_T("N") == strName))		return rtEnd;
		else if (_T("t") == strName)								return rtRMoveTo;
		else if (_T("r") == strName)								return rtRLineTo;
		else if (_T("v") == strName)								return rtRCurveTo;
		else if ((_T("nf") == strName) || (_T("F") == strName))		return rtNoFill;
		else if ((_T("ns") == strName) || (_T("S") == strName))		return rtNoStroke;
		else if ((_T("ae") == strName) || (_T("T") == strName))		return rtAngleEllipseTo;
		else if ((_T("al") == strName) || (_T("U") == strName))		return rtAngleEllipse;
		else if ((_T("at") == strName) || (_T("A") == strName))		return rtArcTo;
		else if ((_T("ar") == strName) || (_T("B") == strName))		return rtArc;
		else if ((_T("wa") == strName) || (_T("W") == strName))		return rtClockwiseArcTo;
		else if ((_T("wr") == strName) || (_T("V") == strName))		return rtClockwiseArc;
		else if ((_T("qx") == strName) || (_T("X") == strName))		return rtEllipticalQuadrX;
		else if ((_T("qy") == strName) || (_T("Y") == strName))		return rtEllipticalQuadrY;
		else if ((_T("qb") == strName) || (_T("Q") == strName))		return rtQuadrBesier;
		else bRes = false;

		return rtEnd;
	}

	static double GetSweepAngle(const double& angleStart, const double& angleEnd)
	{
		if (angleStart >= angleEnd)
			return angleEnd - angleStart;
		else
			return angleEnd - angleStart - 360;
	}

	static std::wstring GetRulerName(RulesType eRuler)
	{
		switch (eRuler)
		{
		case rtOOXMLMoveTo:		{ return _T("moveto"); }
		case rtOOXMLLineTo:		{ return _T("lineto"); }
		case rtOOXMLCubicBezTo:	{ return _T("curveto"); }
		case rtOOXMLArcTo:		{ return _T("ellipseto"); }
		case rtOOXMLQuadBezTo:	{ return _T("qbesier"); }
		case rtOOXMLClose:		{ return _T("close"); }
		case rtOOXMLEnd:		{ return _T("end"); }

		case rtMoveTo:				{ return _T("moveto"); }
		case rtLineTo:				{ return _T("lineto"); }
		case rtCurveTo:				{ return _T("curveto"); }
		
		case rtClose:				{ return _T("close"); }
		case rtEnd:					{ return _T("end"); }
		
		case rtRMoveTo:				{ return _T("rmoveto"); }
		case rtRLineTo:				{ return _T("rlineto"); }
		case rtRCurveTo:			{ return _T("rcurveto"); }
		
		case rtNoFill:				{ return _T("nofill"); }
		case rtNoStroke:			{ return _T("nostroke"); }

		case rtAngleEllipseTo:		{ return _T("ellipseto"); }
		case rtAngleEllipse:		{ return _T("ellipse"); }
		
		case rtArc:					{ return _T("arc"); }
		case rtArcTo:				{ return _T("arcto"); }

		case rtClockwiseArcTo:		{ return _T("clockwisearcto"); }
		case rtClockwiseArc:		{ return _T("clockwisearc"); }

		case rtEllipticalQuadrX:	{ return _T("ellipticalx"); }
		case rtEllipticalQuadrY:	{ return _T("ellipticaly"); }

		case rtQuadrBesier:			{ return _T("qbesier"); }
		default: break;
		};
		return _T("none");
	}

	static long GetCountPoints(RulesType eRuler)
	{
		switch (eRuler)
		{
		case rtOOXMLMoveTo:		return 1;
		case rtOOXMLLineTo:		return 1;
		case rtOOXMLQuadBezTo:	return 2;
		case rtOOXMLCubicBezTo:	return 3;
		case rtOOXMLArcTo:		return 3;//???
		case rtOOXMLClose:		return 0;
		case rtOOXMLEnd:		return 0;
		default: return 0;
		};
		return 0;
	}

	static long GetCountPoints2(RulesType eRuler, LONG lRepeatCount)
	{
		switch (eRuler)
		{
		case rtMoveTo:				
		case rtRMoveTo:
			{ return 1; }
		
		case rtLineTo:		
		case rtRLineTo:
			{ return lRepeatCount; }
		
		case rtCurveTo:		
		case rtRCurveTo:
			{ return 3 * lRepeatCount; }
		
		case rtNoFill:
		case rtNoStroke:
		case rtClose:
		case rtEnd:	
			{ return 0; }
		
		case rtAngleEllipseTo:
		case rtAngleEllipse:
			{ return lRepeatCount; }
		
		case rtArc:
		case rtArcTo:

		case rtClockwiseArcTo:
		case rtClockwiseArc:
			{ return lRepeatCount; }

		case rtEllipticalQuadrX:
		case rtEllipticalQuadrY:
			{ return 1 * lRepeatCount; }

		case rtQuadrBesier:			
			{ return /*2 * */lRepeatCount; }
		case rtFillColor:
		case rtLineColor:
			{
				return 1;
			}
		default: return 3 * lRepeatCount;
		};

		return 0;
	}

	
	class CSlice
	{
	public:
		RulesType m_eRuler;
        std::vector<Aggplus::POINT> m_arPoints;

	private:
		int m_nCountElementsPoint;

	public:
		CSlice(RulesType eType = rtMoveTo)
		{
			m_eRuler = eType;
			m_nCountElementsPoint = 0;
		}

		void AddParam(LONG lParam)
		{
			long lPoint = m_nCountElementsPoint % 2;
			if (0 == lPoint)
			{
                Aggplus::POINT point;
				point.x = lParam;
				point.y = 0;
				m_arPoints.push_back(point);
			}
			else
			{
				m_arPoints[m_arPoints.size() - 1].y = lParam;
			}
			++m_nCountElementsPoint;
		}
		CSlice& operator =(const CSlice& oSrc)
		{
			m_eRuler = oSrc.m_eRuler;
			m_arPoints.clear();
			for (int nIndex = 0; nIndex < oSrc.m_arPoints.size(); ++nIndex)
			{
				m_arPoints.push_back(oSrc.m_arPoints[nIndex]);
			}
			return (*this);
		}		
	protected:
		double GetAngle(double fCentreX, double fCentreY, double fX, double fY)
		{
			//  -   + (..  )
			double dX = fX - fCentreX;
			double dY = fY - fCentreY;

			double modDX = abs(dX);
			double modDY = abs(dY);

			if ((modDX < 0.01) && (modDY < 0.01))
			{
				return 0;
			}
			if ((modDX < 0.01) && (dY < 0))
			{
				return -90;
			}
			else if (modDX < 0.01)
			{
				return 90;
			}
			if ((modDY < 0.01) && (dX < 0))
			{
				return 180;
			}
			else if (modDY < 0.01)
			{
				return 0;
			}

			double fAngle = atan(dY / dX);
			fAngle *= (180 / M_PI);
			if (dX > 0 && dY > 0)
			{
				return fAngle;
			}
			else if (dX > 0 && dY < 0)
			{
				return fAngle;
			}
			else if (dX < 0 && dY > 0)
			{
				//return fAngle + 180;
				return 180 + fAngle;
			}
			else
			{
				//return fAngle + 180;
				return fAngle - 180;
			}
		}

		inline double GetSweepAngle(const double& angleStart, const double& angleEnd)
		{
			if (angleStart >= angleEnd)
				return angleEnd - angleStart;
			else
				return angleEnd - angleStart - 360;
		}

		void ApplyElliptical(bool& bIsX, double& angleStart, double& angleSweet, 
			double& Left, double& Top, double& Width, double& Height, const CGeomShapeInfo::CPointD& pointCur)
		{
			//   (x - y - x...)
			if (bIsX)
			{
				angleStart = -90;
				angleSweet = 90;

				if ((Width < 0) && (Height < 0))
				{
					angleStart = 90;
					Width *= -1;
					Height *= -1;
					Left = pointCur.dX - Width / 2;
					Top = pointCur.dY - Height;
				}
				else if ((Width < 0) && (Height > 0))
				{
					angleStart = -90;
					angleSweet = -90;
					Width *= -1;
					Left = pointCur.dX - Width / 2;
					Top = pointCur.dY;
				}
				else if ((Width > 0) && (Height < 0))
				{
					angleStart = 90;
					angleSweet = -90;
					Height *= -1;
					Left = pointCur.dX - Width / 2;
					Top = pointCur.dY - Height;
				}
				else
				{
					Left = pointCur.dX - Width / 2;
					Top = pointCur.dY;
				}
			}
			else
			{
				angleStart = 180;
				angleSweet = -90;

				if ((Width < 0) && (Height < 0))
				{
					angleStart = 0;
					Width *= -1;
					Height *= -1;
					Left = pointCur.dX - Width;
					Top = pointCur.dY - Height / 2;
				}
				else if ((Width < 0) && (Height > 0))
				{
					angleStart = 0;
					angleSweet = 90;
					Width *= -1;
					Left = pointCur.dX - Width;
					Top = pointCur.dY - Height / 2;
				}
				else if ((Width > 0) && (Height < 0))
				{
					angleStart = 180;
					angleSweet = 90;
					Height *= -1;
					Left = pointCur.dX;
					Top = pointCur.dY - Height / 2;
				}
				else
				{
					Left = pointCur.dX;
					Top = pointCur.dY - Height / 2;
				}
			}
			bIsX = !bIsX;
		}





		void ApplyLimo(CGeomShapeInfo& pGeomInfo, double& lX, double& lY)
		{
			if ((0 == pGeomInfo.m_dLimoX) || (0 == pGeomInfo.m_dLimoY))
				return;

			double dAspect = (double)pGeomInfo.m_dLimoX / pGeomInfo.m_dLimoY;
			double lWidth  = (dAspect * pGeomInfo.m_dHeight);

			if (lWidth < pGeomInfo.m_dWidth)
			{
				// LimoX
				double lXc = pGeomInfo.m_dLeft + pGeomInfo.m_dWidth / 2;
				if ((lX > lXc) || ((lX == lXc) && (pGeomInfo.m_oCurPoint.dX >= lXc)))
				{
					double lXNew = pGeomInfo.m_dLeft + ((lWidth / pGeomInfo.m_dWidth) * (lX - pGeomInfo.m_dLeft));
					lXNew += (pGeomInfo.m_dWidth - lWidth);
					lX = lXNew;
				}
				//if (lX >= lXc)
				//{
				//	LONG lXNew = pGeomInfo->m_lLeft + (LONG)(((double)lWidth / pGeomInfo->m_lWidth) * (lX - pGeomInfo->m_lLeft));
				//	if (pGeomInfo->m_oCurPoint.x >= lXc)
				//	{
				//		lXNew += (pGeomInfo->m_lWidth - lWidth);
				//	}
				//	lX = lXNew;
				//}
			}
			else if (lWidth != pGeomInfo.m_dWidth)
			{
				// LimoY
				double lHeight = (pGeomInfo.m_dWidth / dAspect);
				double lYc = pGeomInfo.m_dTop + pGeomInfo.m_dHeight / 2;
				if ((lY > lYc) || ((lY == lYc) && (pGeomInfo.m_oCurPoint.dY >= lYc)))
				{
					double lYNew = pGeomInfo.m_dTop + ((lHeight / pGeomInfo.m_dHeight) * (lY - pGeomInfo.m_dTop));
					lYNew += (pGeomInfo.m_dHeight - lHeight);
					lY = lYNew;
				}
			}
		}

		void Bez2_3(std::vector<CGeomShapeInfo::CPointD>& oArray, RulesType& eType)
		{
			if (rtQuadrBesier == eType)
			{
				eType = rtCurveTo;
			}
			else if (rtOOXMLQuadBezTo == eType)
			{
				eType = rtOOXMLCubicBezTo;
			}
			else
			{
				return;
			}
			
			std::vector<CGeomShapeInfo::CPointD> arOld;
			arOld.insert(arOld.end(),oArray.begin(), oArray.end());

			oArray.clear();
			
			size_t nStart	= 0;
			size_t nEnd	= 2;

			size_t nCount = arOld.size();
			while (nStart < (nCount - 1))
			{
				if (2 >= (nCount - nStart))
				{
					// �� ���� ������ ���� �� �����
					for (size_t i = nStart; i < nCount; ++i)
					{
						oArray.push_back(arOld[i]);
					}
					
					nStart = nCount;
					break;
				}
				
				if (4 == (nCount - nStart))
				{
					// ������ �� ���������... ������ ������ �������� �������
					oArray.push_back(arOld[nStart]);
					oArray.push_back(arOld[nStart + 1]);
					oArray.push_back(arOld[nStart + 2]);
					oArray.push_back(arOld[nStart + 3]);

					nStart += 4;
					break;
				}

				// ������ ���� ���
				CGeomShapeInfo::CPointD mem1;
				mem1.dX = (arOld[nStart].dX + 2 * arOld[nStart + 1].dX) / 3.0;
				mem1.dY = (arOld[nStart].dY + 2 * arOld[nStart + 1].dY) / 3.0;

				CGeomShapeInfo::CPointD mem2;
				mem2.dX = (2 * arOld[nStart + 1].dX + arOld[nStart + 2].dX) / 3.0;
				mem2.dY = (2 * arOld[nStart + 1].dY + arOld[nStart + 2].dY) / 3.0;

				oArray.push_back(mem1);
				oArray.push_back(mem2);
				oArray.push_back(arOld[nStart + 2]);

				nStart += 2;
			}
		}
	};

	class CPartPath
	{
	public:
		bool m_bFill;
		bool m_bStroke;
		long width;
		long height;
		std::vector<CSlice> m_arSlices;

	public:
		CPartPath() : m_arSlices()
		{
			m_bFill = true;
			m_bStroke = true;
			width = 43200;
			height = 43200;
		}
	#if defined(PPTX_DEF)
		void FromXML(XmlUtils::CXmlNode& PathNode, NSGuidesOOXML::CFormulaManager& pManager)
		{
			m_bFill = PathNode.GetAttribute(_T("fill"), _T("norm")) != _T("none");
			std::wstring stroke = PathNode.GetAttribute(_T("stroke"), _T("true"));
			m_bStroke = (stroke == _T("true")) || (stroke == _T("1"));
			width = (long)XmlUtils::GetInteger(PathNode.GetAttribute(_T("w"), _T("0")));
			height = (long)XmlUtils::GetInteger(PathNode.GetAttribute(_T("h"), _T("0")));
			if(width == 0) width = (long)pManager.GetWidth();
			if(height == 0) height = (long)pManager.GetHeight();

			XmlUtils::CXmlNodes list;
			PathNode.GetNodes(_T("*"), list);
			for(long i = 0; i < list.GetCount(); i++)
			{
				CSlice slice;
				XmlUtils::CXmlNode node;
				list.GetAt(i, node);
				slice.FromXML(node, pManager, pManager.GetWidth()/width, pManager.GetHeight()/height);
				m_arSlices.push_back(slice);
			}

			//CSlice EndSlice;
			//EndSlice.m_eRuler = rtEnd;
			//m_arSlices.push_back(EndSlice);
		}
	#endif
	#if defined(PPT_DEF)
		void FromXML(std::wstring strPath, NSGuidesVML::CFormulasManager& pManager)
		{
			NSStringUtils::CheckPathOn_Fill_Stroke(strPath, m_bFill, m_bStroke);
			std::vector<std::wstring> oArray;

			NSStringUtils::ParsePath2(strPath, &oArray);

			ParamType eParamType = ptValue;
			RulesType eRuler = rtEnd; 
			LONG lValue;
			bool bRes = true;

			for (int nIndex = 0; nIndex < oArray.size(); ++nIndex)
			{
				lValue = GetValue(oArray[nIndex], eParamType, bRes);
				if (bRes)
				{	
					switch (eParamType)
					{
					case ptFormula: { lValue = pManager.m_arResults[lValue]; break; }
					case ptAdjust:  { lValue = (*(pManager.m_pAdjustments))[lValue]; break; }
					default: break;
					};
					if (0 != m_arSlices.size())
					{
						m_arSlices[m_arSlices.size() - 1].AddParam(lValue);
					}
				}
				else
				{
					eRuler = GetRuler(oArray[nIndex], bRes);
					if (bRes)
					{
						if (rtNoFill == eRuler)
						{
							m_bFill = false;
						}
						else if (rtNoStroke == eRuler)
						{
							m_bStroke = false;
						}
						else
						{				
							CSlice oSlice(eRuler);
							m_arSlices.push_back(oSlice);
						}
					}
				}
			}
		}
	#endif

		CPartPath& operator =(const CPartPath& oSrc)
		{
			m_bFill = oSrc.m_bFill;
			m_bStroke = oSrc.m_bStroke;

			width = oSrc.width;
			height = oSrc.height;

			m_arSlices.clear();
			for (int nIndex = 0; nIndex < oSrc.m_arSlices.size(); ++nIndex)
			{
				m_arSlices.push_back(oSrc.m_arSlices[nIndex]);
			}
			return (*this);
		}
	};

	class CPath
	{
	public:
		std::vector<CPartPath> m_arParts;

		//std::wstring ToXml(CGeomShapeInfo& pGeomInfo, double dStartTime, double dEndTime, CPen& pPen, CBrush& pFore, CMetricInfo& pInfo, NSBaseShape::ClassType ClassType)
		//{
		//	std::wstring strResult = _T("");
		//	for (int nIndex = 0; nIndex < m_arParts.size(); ++nIndex)
		//	{
		//		strResult += m_arParts[nIndex].ToXml(pGeomInfo, dStartTime, dEndTime, pPen, pFore, pInfo, ClassType);
		//	}
		//	return strResult;
		//}

		//void ToRenderer(IRenderer* pRenderer, CGeomShapeInfo& pGeomInfo, double dStartTime, 
		//	double dEndTime, CPen& pPen, CBrush& pFore, CMetricInfo& pInfo, NSBaseShape::ClassType ClassType)
		//{
		//	CGraphicPath oPath;
		//	oPath.Pen	= pPen;
		//	oPath.Brush	= pFore;

		//	int nSize = m_arParts.size();
		//	for (int nIndex = 0; nIndex < nSize; ++nIndex)
		//	{
		//		oPath.Clear();
		//		m_arParts[nIndex].ToRenderer(&oPath, pGeomInfo, dStartTime, dEndTime, pPen, pFore, pInfo, ClassType);

		//		oPath.Draw(pRenderer);
		//	}
		//}

		CPath& operator =(const CPath& oSrc)
		{
			m_arParts.clear();
			for (int nIndex = 0; nIndex < oSrc.m_arParts.size(); ++nIndex)
			{
				m_arParts.push_back(oSrc.m_arParts[nIndex]);
			}
			return (*this);
		}

		void SetCoordsize(LONG lWidth, LONG lHeight)
		{
			for (int nIndex = 0; nIndex < m_arParts.size(); ++nIndex)
			{
				m_arParts[nIndex].width		= lWidth;
				m_arParts[nIndex].height	= lHeight;
			}
		}
	};
}