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
Selected product:	STA350BW
***********************************************************************************/


Speaker_EQ_Table_48000[] = {
	0x80252C,0x7F931F,0x7FDB07,0x8049AC,0x4011CC,    // 48KFs, Biquad1, Address: 0x00~0x04 (stability: 0.9989)
	0x808BDF,0x7F10AB,0x7F7421,0x81154F,0x3FED03,    // 48KFs, Biquad2, Address: 0x05~0x09 (stability: 0.9958)
	0x800054,0x7CBBD4,0x7C6BBB,0x870518,0x41B138,    // 48KFs, Biquad3, Address: 0x0A~0x0E (stability: 0.9722)
	0x8CE96A,0x691763,0x731696,0x949522,0x4129BD,    // 48KFs, Biquad4, Address: 0x0F~0x13 (stability: 0.9161)
	0x000000,0x000000,0x000000,0x000000,0x400000     // 48KFs, Biquad5, Address: 0x14~0x18 (stability: 0.0000)
};
