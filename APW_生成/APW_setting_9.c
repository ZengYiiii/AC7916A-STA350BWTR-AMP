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


Creation date:		Wednesday, 01/May/'24
Tool revision:		APW v2.100
Selected product:	STA380BW
***********************************************************************************/


Speaker_EQ_Table_48000[] = {
	0xE2F05A,0x1BD299,0x1D0FA6,0xE4107A,0x100E76,    // 48KFs, Biquad1, Address: 0x14~0x18 (stability: 0.9343)
	0xE73655,0x17259C,0x18C9AB,0xE78498,0x10AAE6,    // 48KFs, Biquad2, Address: 0x19~0x1D (stability: 0.8747)
	0xEC213F,0x156A4B,0x13DEC1,0xEBBE71,0x0F6BA2,    // 48KFs, Biquad3, Address: 0x1E~0x22 (stability: 0.7956)
	0x000000,0x000000,0x000000,0x000000,0x100000,    // 48KFs, Biquad4, Address: 0x23~0x27 (stability: 0.0000)
	0xE2F05A,0x1BD299,0x1D0FA6,0xE4107A,0x100E76,    // 48KFs, Biquad5, Address: 0x14~0x18 (stability: 0.9343)
	0x0E0C58                                         // 48KFs, Coefficients 0x00~0x27 checksum
};
