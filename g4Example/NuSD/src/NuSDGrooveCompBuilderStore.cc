

#include "G4Types.hh"
#include "NuSDGrooveCompBuilderStore.hh"
#include "G4GeometryManager.hh"


#include "G4AutoLock.hh"

namespace
{
  G4Mutex mapMutex = G4MUTEX_INITIALIZER;
}

// ***************************************************************************
// Static class variables
// ***************************************************************************
//
NuSDGrooveCompBuilderStore* NuSDGrooveCompBuilderStore::fInstance = nullptr;

G4ThreadLocal G4bool NuSDGrooveCompBuilderStore::locked = false;

// ***************************************************************************
// Protected constructor: Construct underlying container with
// initial size of 100 entries
// ***************************************************************************
//
NuSDGrooveCompBuilderStore::NuSDGrooveCompBuilderStore()
  : std::vector<NuSDVGrooveCompBuilder*>()
{
  reserve(20);
}

// ***************************************************************************
// Destructor
// ***************************************************************************
//
NuSDGrooveCompBuilderStore::~NuSDGrooveCompBuilderStore()
{
  //Clean();  // Delete all volumes in the store
}

// ***************************************************************************
// Delete all elements from the store
// ***************************************************************************
//
void NuSDGrooveCompBuilderStore::Clean()
{
  
  std::size_t i=0;
  NuSDGrooveCompBuilderStore* store = GetInstance();

  for(auto pos=store->cbegin(); pos!=store->cend(); ++pos)
  {
    G4cout<<"Deleting groove builder component: "<<(*pos)->GetName()<<" ..."<<G4endl;
    delete *pos; ++i;
  }

  locked = false;
  store->clear();
}

// ***************************************************************************
// Add Volume to container
// ***************************************************************************
//
void NuSDGrooveCompBuilderStore::Register(NuSDVGrooveCompBuilder* pGrooveCompBuilder)
{
  NuSDGrooveCompBuilderStore* store = GetInstance();
  store->push_back(pGrooveCompBuilder);
  
}


// ***************************************************************************
// Return ptr to Store, setting if necessary
// ***************************************************************************
//
NuSDGrooveCompBuilderStore* NuSDGrooveCompBuilderStore::GetInstance()
{
  static NuSDGrooveCompBuilderStore worldStore;
  if (fInstance == nullptr)
  {
    fInstance = &worldStore;
  }
  return fInstance;
}
