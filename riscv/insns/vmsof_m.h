// vmsof.m rd, vs2, vm
require(P.VU.vsew >= e8 && P.VU.vsew <= e64);
require_vector(true);
require(P.VU.vstart->read() == 0);
require_vm;
require(insn.rd() != insn.rs2());

reg_t vl = P.VU.vl->read();
reg_t rd_num = insn.rd();
reg_t rs2_num = insn.rs2();


// printf("\n----- vmsbf.m -----\n");

bool has_one = false;
int remaining_vl=vl;
reg_t res;
for (reg_t midx=0; midx*64<vl; ++midx)
{
    reg_t vl_mask = remaining_vl>63?~0ULL:(1ULL << remaining_vl)-1 ;
    reg_t source = P.VU.elt<uint64_t>(rs2_num, midx) & vl_mask;;
    reg_t mask   = P.VU.elt<uint64_t>(0, midx);
    if (insn.v_vm()==0) source = source & mask;

    if (has_one) 
    {
        res = 0ULL;
    }
    else
    {
        int zero_count = __builtin_ctzll(source);
        res = source==0? 0 : (1 << zero_count);
    }

    uint64_t& vd = P.VU.elt<uint64_t>(rd_num, midx);
    if (insn.v_vm()==0) res = (P.VU.vma) ? (res|~mask) : ((vd&~mask)|(res&mask));
    vd &= ~vl_mask;
    vd |= res&vl_mask;

    if (source!=0) has_one=true;
    remaining_vl -= 64;
}

// bool has_one = false;
// for (reg_t i = P.VU.vstart->read() ; i < vl; ++i) {
//   const int midx = i / 64;
//   const int mpos = i % 64;
//   const uint64_t mmask = UINT64_C(1) << mpos; \

//   bool vs2_lsb = ((P.VU.elt<uint64_t>(rs2_num, midx ) >> mpos) & 0x1) == 1;
//   bool do_mask = (P.VU.elt<uint64_t>(0, midx) >> mpos) & 0x1;

//   if (insn.v_vm() == 1 || (insn.v_vm() == 0 && do_mask)) {
//     uint64_t &vd = P.VU.elt<uint64_t>(rd_num, midx, true);
//     uint64_t res = 0;
//     if (!has_one && vs2_lsb) {
//       has_one = true;
//       res = 1;
//     }
//     vd = (vd & ~mmask) | ((res << mpos) & mmask);
//   }
// }

V_HANDLE_TAIL_MASK_OPERATION_EEW_TA_NOVL_M(VEC_VLS(SE_GET_VLS_VD,int8_t), 8)