/***********************************************************************************
                     Sound Terminal coefficients array
                          Created with APWorkbench

No warranty:                                                                       
  THIS SOFTWARE IS PROVIDED BY ST "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY, OF         
  SATISFACTORY QUALITY, AND FITNESS FOR A PARTICULAR PURPOSE OR USE ARE            
  DISCLAIMED. ST MAKES NO REPRESENTATION THAT THE SOFTWARE WILL NOT INFRINGE ANY   
  PATENT, COPYRIGHT, TRADE SECRET OR OTHER PROPRIETARY RIGHT OF A THIRD PARTY.     
  ST does not warrant that use in whole or in part of the Software will be         
  uninterrupted or error free, will meet your requirements, or will operate with   
  the combination of hardware and software selected by you.                        
                                                                                   
  ST is under no obligation to provide bug fixes, patches, upgrades or other       
  enhancements or derivatives of the features, functionality or performance of     
  this Software.                                                                   
                                                                                   
  ALL WARRANTIES, CONDITIONS OR OTHER TERMS IMPLIED BY LAW ARE EXCLUDED TO THE     
  FULLEST EXTENT PERMITTED BY LAW.                                                 
                                                                                   
  You acknowledge that the Software, and processes and products related thereto    
  are not designed nor authorized for use in life supporting devices. You agree    
  to hold ST free and harmless from any liability in connection with the use of    
  the Software and products or processes related in any way thereto.               
                                                                                   
No liability:                                                                      
  ST SHALL HAVE NO LIABILITY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL,            
  CONSEQUENTIAL, EXEMPLARY, OR PUNITIVE DAMAGES OF ANY CHARACTER INCLUDING,        
  WITHOUT LIMITATION, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, LOSS OF USE,    
  DATA OR PROFITS, OR BUSINESS INTERRUPTION, HOWEVER CAUSED AND ON ANY THEORY OF   
  CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE), PRODUCT LIABILITY OR            
  OTHERWISE, ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED   
  OF THE POSSIBILITY OF SUCH DAMAGES.                                              


Creation date:		Sunday, 21/April/'24
Tool revision:		APW v2.100
Selected product:	STA350BW
***********************************************************************************/


Speaker_EQ_Table_48000[] = {
	{0x14,0x802F6F},{0x15,0x7F3CBB},{0x16,0x7FD091},{0x17,0x805DFE},{0x18,0x4032A3},    // 48KFs, Biquad1, Address: 0x14~0x18 (stability: 0.9986)
	{0x19,0x80A184},{0x1A,0x7F0690},{0x1B,0x7F5E7C},{0x1C,0x813FD7},{0x1D,0x3FDCCC},    // 48KFs, Biquad2, Address: 0x19~0x1D (stability: 0.9951)
	{0x1E,0x80D85B},{0x1F,0x7E300C},{0x20,0x7F27A5},{0x21,0x819F86},{0x22,0x401837},    // 48KFs, Biquad3, Address: 0x1E~0x22 (stability: 0.9936)
	{0x23,0x880886},{0x24,0x723016},{0x25,0x77F77A},{0x26,0x8C2087},{0x27,0x40D7B1},    // 48KFs, Biquad4, Address: 0x23~0x27 (stability: 0.9515)
	{0x14,0x802F6F},{0x15,0x7F3CBB},{0x16,0x7FD091},{0x17,0x805DFE},{0x18,0x4032A3},    // 48KFs, Biquad5, Address: 0x14~0x18 (stability: 0.9986)
	{0x19,0x80A184},{0x1A,0x7F0690},{0x1B,0x7F5E7C},{0x1C,0x813FD7},{0x1D,0x3FDCCC},    // 48KFs, Biquad6, Address: 0x19~0x1D (stability: 0.9951)
	{0x1E,0x80D85B},{0x1F,0x7E300C},{0x20,0x7F27A5},{0x21,0x819F86},{0x22,0x401837},    // 48KFs, Biquad7, Address: 0x1E~0x22 (stability: 0.9936)
	{0x28,0xEC481A},{0x29,0x1820F9},{0x2A,0x13A9C9},{0x2B,0xE7E57C},{0x2C,0x400AE2}     // 48KFs, Biquad8, Address: 0x28~0x2C (stability: 0.4339)
};
