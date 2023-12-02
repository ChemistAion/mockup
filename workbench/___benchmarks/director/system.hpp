#pragma once

namespace Primitives
{	
	constexpr std::size_t count = 1u << 16u;

	struct FeatureTestA
	{
	};

	struct FeatureTestAB
	{
	};

	struct FeatureTestABC
	{
	};

	////////////////////////////////////////////////////////////////////////////////

	struct TestComponentA
	{
		std::uint64_t test_ = 0;

		TestComponentA() = default;
		TestComponentA(std::uint64_t test)
			: test_(test)
		{
		}
	};

	struct TestComponentAB
	{
		std::uint64_t test_ = 0;
		TestComponentA componentA_;

		TestComponentAB() = default;
		TestComponentAB(std::uint64_t test, const TestComponentA& componentA)
			: test_(test)
			, componentA_(componentA)
		{
		}
	};

	struct TestComponentABC
	{
		std::uint64_t test_ = 0;
		TestComponentA componentA_;
		TestComponentAB componentAB_;

		TestComponentABC() = default;
		TestComponentABC(std::uint64_t test, const TestComponentA& componentA, const TestComponentAB& componentAB)
			: test_(test)
			, componentA_(componentA)
			, componentAB_(componentAB)
		{
		}
	};

	////////////////////////////////////////////////////////////////////////////////

	struct TestEventA
	{
		std::uint64_t test_ = 0;

//		TestEventA() = default;
		TestEventA(std::uint64_t test)
			: test_(test)
		{
		}
	};

	struct TestEventAB
	{
		std::uint64_t test_ = 0;
		TestEventA eventA_;

//		TestEventAB() = default;
		TestEventAB(std::uint64_t test, const TestEventA& eventA)
			: test_(test)
			, eventA_(eventA)
		{
		}
	};

	struct TestEventABC
	{
		std::uint64_t test_ = 0;
		TestEventA eventA_;
		TestEventAB eventAB_;

//		TestEventABC() = default;
		TestEventABC(std::uint64_t test, const TestEventA& eventA, const TestEventAB& eventAB)
			: test_(test)
			, eventA_(eventA)
			, eventAB_(eventAB)
		{
		}
	};

	////////////////////////////////////////////////////////////////////////////////

	class TestSystemA : public System<TestEventA>
	{
		std::uint64_t test_ = 0;
	public:
		TestSystemA(std::uint64_t test)
			: test_(test)
		{
		}

		void Process(Registry& owner, const TestEventA& eventA) override
		{
//			owner.GetView<TestComponentA, TestComponentAB, TestComponentABC>().Each
//			(
//				[this, &eventA](auto&&, TestComponentA& componentA, TestComponentAB& componentAB, TestComponentABC& componentABC)
//				{
//					componentA.test_ += eventA.test_ * test_;
//		
//					componentAB.test_ += eventA.test_ * test_;
//					componentAB.componentA_.test_ += eventA.test_ * test_;
//		
//					componentABC.test_ += eventA.test_ * test_;
//					componentABC.componentA_.test_ += eventA.test_ * test_;
//					componentABC.componentAB_.test_ += eventA.test_ * test_;
//					componentABC.componentAB_.componentA_.test_ += eventA.test_ * test_;
//				}
//			);
		}
	};

	class TestSystemAB : public System<TestEventA, TestEventAB>
	{
		std::uint64_t test_ = 0;
	public:
		TestSystemAB(std::uint64_t test)
			: test_(test)
		{
		}

		void Process(Registry& owner, const TestEventA& eventA) override
		{
//			owner.GetView<TestComponentA, TestComponentAB>().Each
//			(
//				[this, &eventA](auto&&, TestComponentA& componentA, TestComponentAB& componentAB)
//				{
//					componentA.test_ += eventA.test_ * test_;
//		
//					componentAB.test_ += eventA.test_ * test_;
//					componentAB.componentA_.test_ += eventA.test_ * test_;
//				}
//			);
		}
		
		void Process(Registry& owner, const TestEventAB& eventAB) override
		{
//			owner.GetView<TestComponentA, TestComponentAB>().Each
//			(
//				[this, &eventAB](auto&&, TestComponentA& componentA, TestComponentAB& componentAB)
//				{
//					componentA.test_ += eventAB.test_ * test_;
//					componentA.test_ -= eventAB.eventA_.test_ * test_;
//		
//					componentAB.test_ += eventAB.test_ * test_;
//					componentAB.test_ -= eventAB.eventA_.test_ * test_;
//					componentAB.componentA_.test_ += eventAB.test_ * test_;
//					componentAB.componentA_.test_ -= eventAB.eventA_.test_ * test_;
//				}
//			);
		}
	};

	class TestSystemABC : public System<TestEventA, TestEventAB, TestEventABC>
	{
		std::uint64_t test_ = 0;
	public:
		TestSystemABC(std::uint64_t test)
			: test_(test)
		{
		}

		void Process(Registry& owner, const TestEventA& eventA) override
		{
//			owner.GetView<TestComponentA>().Each
//			(
//				[this, &eventA](auto&&, TestComponentA& componentA)
//				{
//					componentA.test_ += eventA.test_ * test_;
//				}
//			);
		}
//		
		void Process(Registry& owner, const TestEventAB& eventAB) override
		{
//			owner.GetView<TestComponentA>().Each
//			(
//				[this, &eventAB](auto&&, TestComponentA& componentA)
//				{
//					componentA.test_ += eventAB.test_ * test_;
//					componentA.test_ -= eventAB.eventA_.test_ * test_;
//				}
//			);
		}
		
		void Process(Registry& owner, const TestEventABC& eventABC) override
		{
//			owner.GetView<TestComponentA>().Each
//			(
//				[this, &eventABC](auto&&, TestComponentA& componentA)
//				{
//					componentA.test_ += eventABC.test_ * test_;				
//					componentA.test_ += eventABC.eventA_.test_ * test_;
//					componentA.test_ -= eventABC.eventAB_.test_ * test_;
//					componentA.test_ -= eventABC.eventAB_.eventA_.test_ * test_;
//				}
//			);
		}
	};
}