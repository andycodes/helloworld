#include <stdio.h>
#include <assert.h>
#include "os.h"
#include "smmuv3.h"

#define DEBUG

static struct smmuv3* smmu = (struct smmuv3*)SMMU_BASE_ADDR;

void dump_smmu_idr0(void)
{
	/*
	 * FVP model:
	 * 	 pci.pci_smmuv3.mmu.SMMU_IDR0=135259839
	 */
	//assert(smmu->SMMU_IDR0 == 0x80fe6bf);

#ifdef DEBUG

	printk("SMMU_IDR0: 0x%x\n", smmu->SMMU_IDR0);
	printk("\t ST_LEVEL: %u\n", GET_FIELD(SMMU_IDR0, ST_LEVEL_MASK, ST_LEVEL_SHIFT));
	printk("\t TERM_MODEL: %u\n", GET_FIELD(SMMU_IDR0, TERM_MODEL_MASK, TERM_MODEL_SHIFT));
	printk("\t STALL_MODEL: %u\n", GET_FIELD(SMMU_IDR0, STALL_MODEL_MASK, STALL_MODEL_SHIFT));
	printk("\t ATSRECERR: %u\n", GET_FIELD(SMMU_IDR0, ATSRECERR_MASK, ATSRECERR_SHIFT));
	printk("\t TTENDIAN: %u\n", GET_FIELD(SMMU_IDR0, TTENDIAN_MASK, TTENDIAN_SHIFT));
	printk("\t VATOS: %u\n", GET_FIELD(SMMU_IDR0, VATOS_MASK, VATOS_SHIFT));
	printk("\t CD2L: %u\n", GET_FIELD(SMMU_IDR0, CD2L_MASK, CD2L_SHIFT));
	printk("\t VMID16: %u\n", GET_FIELD(SMMU_IDR0, VMID16_MASK, VMID16_SHIFT));
	printk("\t VMW: %u\n", GET_FIELD(SMMU_IDR0, VMW_MASK, VMW_SHIFT));
	printk("\t PRI: %u\n", GET_FIELD(SMMU_IDR0, PRI_MASK, PRI_SHIFT));
	printk("\t ATOS: %u\n", GET_FIELD(SMMU_IDR0, ATOS_MASK, ATOS_SHIFT));
	printk("\t SEV: %u\n", GET_FIELD(SMMU_IDR0, SEV_MASK, SEV_SHIFT));
	printk("\t MSI: %u\n", GET_FIELD(SMMU_IDR0, MSI_MASK, MSI_SHIFT));
	printk("\t ASID16: %u\n", GET_FIELD(SMMU_IDR0, ASID16_MASK, ASID16_SHIFT));
	printk("\t NS1ATS: %u\n", GET_FIELD(SMMU_IDR0, NS1ATS_MASK, NS1ATS_SHIFT));
	printk("\t ATS: %u\n", GET_FIELD(SMMU_IDR0, ATS_MASK, ATS_SHIFT));
	printk("\t HYP: %u\n", GET_FIELD(SMMU_IDR0, HYP_MASK, HYP_SHIFT));
	printk("\t HTTU: %u\n", GET_FIELD(SMMU_IDR0, HTTU_MASK, HTTU_SHIFT));
	printk("\t BTM: %u\n", GET_FIELD(SMMU_IDR0, BTM_MASK, BTM_SHIFT));
	printk("\t COHACC: %u\n", GET_FIELD(SMMU_IDR0, COHACC_MASK, COHACC_SHIFT));
	printk("\t TTF: %u\n", GET_FIELD(SMMU_IDR0, TTF_MASK, TTF_SHIFT));
	printk("\t S1P: %u\n", GET_FIELD(SMMU_IDR0, S1P_MASK, S1P_SHIFT));
	printk("\t S2P: %u\n", GET_FIELD(SMMU_IDR0, S2P_MASK, S2P_SHIFT));
#endif

}
