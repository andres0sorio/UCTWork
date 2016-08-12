// $Id: $
int LookUp( int lPhi , int nTowers ) 
{
  
  int itrVal = (nTowers/2)+abs(lPhi-nTowers);
  std::cout  << itrVal << std::endl;
  
  if ( itrVal < nTowers) 
    return itrVal;
  else return nTowers;
  
}
