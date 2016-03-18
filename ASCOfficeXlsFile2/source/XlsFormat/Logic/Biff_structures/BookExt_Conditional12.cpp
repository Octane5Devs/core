
#include "BookExt_Conditional12.h"
#include <Binary/CFRecord.h>

namespace XLS
{


BiffStructurePtr BookExt_Conditional12::clone()
{
	return BiffStructurePtr(new BookExt_Conditional12(*this));
}



void BookExt_Conditional12::store(CFRecord& record)
{
	unsigned char flags = 0;
	SETBIT(flags, 1, fPublishedBookItems);
	SETBIT(flags, 2, fShowPivotChartFilter);
	record << flags;
}


void BookExt_Conditional12::load(CFRecord& record)
{
	unsigned char flags;
	record >> flags;
	fPublishedBookItems = GETBIT(flags, 1);
	fShowPivotChartFilter = GETBIT(flags, 2);
}


} // namespace XLS

