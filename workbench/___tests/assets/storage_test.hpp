#include "assets.hpp"

#include <future>

namespace Primitives
{
	struct DummyStorage : public Storage<std::string>
	{
		virtual void LoadAsset(Storage::Future& future, const std::string& name) override
		{
		}

		virtual void SaveAsset(Storage::Future& future, const std::string& name) override
		{
		}
	};

	struct SimpleStorage : public Storage<std::string>
	{
		int value_ = 0;
		
		SimpleStorage() = delete;
		
		explicit SimpleStorage(int value)
		{
			value_ = value;
		}

		virtual void LoadAsset(Storage::Future& future, const std::string& name) override
		{
		}

		virtual void SaveAsset(Storage::Future& future, const std::string& name) override
		{
		}
	};

//		struct ParallelDummyStorage : public Storage<std::string>
//		{
//			std::shared_ptr<Parallel::Scheduler> scheduler_;
//	
//			ParallelDummyStorage() = default;
//	
//			explicit ParallelDummyStorage(std::shared_ptr<Parallel::Scheduler> scheduler)
//			{
//				scheduler_ = scheduler;
//			}
//	
//			virtual bool LoadFromFile(Storage::Future& future, const std::string& name) override
//			{
//				if (!scheduler_)
//				{
//					return false;
//				}
//	
//				EntryType result;
//	
//				auto Fallback = [output = result, name]() mutable
//				{
//					output.name_ = name;
//					return output;
//				};
//	
//				future = scheduler_->AddImmediateTask(Fallback);
//	
//				return true;
//			}
//	
//	//		virtual bool LoadFromInstance(Storage::Future&, const std::string&, Storage::Instance) override
//	//		{
//	//			return false;
//	//		}
//	//		
//	//		virtual bool LoadFromMemory(Storage::Future&, const std::string&, const void*, std::size_t) override
//	//		{
//	//			return false;
//	//		}
//		};
}