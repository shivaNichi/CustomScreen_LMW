/* CPotManager.hpp */

#ifndef _CPOTMANAGER_HPP_
#define _CPOTMANAGER_HPP_

extern struct PotInfo *pInfo;
extern union tooldata tData;

struct PotInfo{
	unsigned short usTotTool;		// Total Number of Tools
	unsigned short usTotPages;		// Total Nuber of pages
	unsigned short usPotsPerPage;	// Number of Pots Per page
	unsigned short usRemainPots;	// Remaining Pots
	unsigned short usInitIndex[3];	// To store the Starting address of the device
	unsigned short usPageNo;		// Current page number
};

union tooldata{				
	 struct {
		unsigned b0:1;
		unsigned b1:1;
		unsigned b2:1;
		unsigned b3:1;
		unsigned b4:1;
		unsigned b5:1;
		unsigned b6:1;
		unsigned b7:1;
		unsigned b8:1;
		unsigned b9:1;
		unsigned b10:1;
		unsigned b11:1;
		unsigned b12:1;
		unsigned b13:1;
		unsigned b14:1;
		unsigned b15:1;
	}bits;
  unsigned int num;
};
	static unsigned short usRCcount=1; // Row Col Count

	int InitPotInfo();			
	void GetPotInfo(PotInfo *pt);
	void SetPotInfo(PotInfo *pt);

#endif	/* _CPOTMANAGER_HPP_ */