#include "allocator_test.hpp"

//	TEST_F(Engine, DISABLED_Allocator_LinearBasicAllocation)
//	{
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			decltype(context_) error;
//	
//			AllocatorLinear linear(error, 1024);
//	
//			auto element128_1 = linear.Allocate(128, 1);
//			auto element128_2 = linear.Allocate(128, 2);
//			auto element128_4 = linear.Allocate(128, 4);
//			auto element128_8 = linear.Allocate(128, 8);
//	
//			ASSERT_FALSE(element128_1.first);
//			ASSERT_FALSE(element128_2.first);
//			ASSERT_FALSE(element128_4.first);
//			ASSERT_FALSE(element128_8.first);
//	
//			ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//			ASSERT_EQ(linear.GetPagePoolSize(), 0);
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			AllocatorLinear linear(context_, 64);
//	
//			auto element64_1 = linear.Allocate(64, 1);
//			auto element128_4 = linear.Allocate(128, 4);
//			auto element64_2 = linear.Allocate(64, 2);
//			auto element128_8 = linear.Allocate(128, 8);
//	
//			ASSERT_TRUE(element64_1.first);
//			ASSERT_TRUE(element64_2.first);
//			ASSERT_FALSE(element128_4.first);
//			ASSERT_FALSE(element128_8.first);
//	
//			ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//			ASSERT_EQ(linear.GetPagePoolSize(), 2);
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			AllocatorLinear linear(context_, 32);
//	
//			auto element32_1 = linear.Allocate(32, 1);
//			auto element16_2 = linear.Allocate(16, 2);
//			auto element32_4 = linear.Allocate(32, 4);
//			auto element16_8 = linear.Allocate(16, 8);
//			auto element16_16 = linear.Allocate(16, 16);
//	
//			ASSERT_TRUE(element32_1.first);
//			ASSERT_TRUE(element16_2.first);
//			ASSERT_TRUE(element32_4.first);
//			ASSERT_TRUE(element16_8.first);
//			ASSERT_TRUE(element16_16.first);
//	
//			ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//			ASSERT_EQ(linear.GetPagePoolSize(), 4);
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			AllocatorLinear linear(context_, 1024);
//	
//			auto element128_16 = linear.Allocate(128, 16);
//			auto element128_32 = linear.Allocate(128, 32);
//			auto element128_64= linear.Allocate(128, 64);
//			auto element128_128 = linear.Allocate(128, 128);
//			auto element256_256 = linear.Allocate(256, 256);
//			auto element256_128 = linear.Allocate(256, 128);
//			auto element256_64 = linear.Allocate(256, 64);
//			auto element256_32 = linear.Allocate(256, 32);
//			auto element256_16 = linear.Allocate(256, 16);
//	
//			ASSERT_TRUE(element128_16.first);
//			ASSERT_TRUE(element128_32.first);
//			ASSERT_TRUE(element128_64.first);
//			ASSERT_TRUE(element128_128.first);
//			ASSERT_TRUE(element256_16.first);
//			ASSERT_TRUE(element256_32.first);
//			ASSERT_TRUE(element256_64.first);
//			ASSERT_TRUE(element256_128.first);
//			ASSERT_TRUE(element256_256.first);
//	
//			ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//			ASSERT_EQ(linear.GetPagePoolSize(), 2);
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	}
//	
//	TEST_F(Engine, DISABLED_Allocator_LinearAllignmentAllocation)
//	{
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			AllocatorLinear linear(context_, 256);
//	
//			auto element16_16 = linear.Allocate(16, 16);
//			auto element32_32 = linear.Allocate(32, 32);
//			auto element64_64 = linear.Allocate(64, 64);
//			auto element128_128 = linear.Allocate(128, 128);
//			auto element256_256 = linear.Allocate(256, 256);
//	
//			ASSERT_TRUE(element16_16.first);
//			ASSERT_TRUE(element32_32.first);
//			ASSERT_TRUE(element64_64.first);
//			ASSERT_TRUE(element128_128.first);
//			ASSERT_TRUE(element256_256.first);
//	
//			ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//			ASSERT_EQ(linear.GetPagePoolSize(), 2);
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			AllocatorLinear linear(context_, 8);
//	
//			auto element8_1 = linear.Allocate(8, 1);
//			auto element8_2 = linear.Allocate(8, 2);
//			auto element8_4 = linear.Allocate(8, 4);
//			auto element8_8 = linear.Allocate(8, 8);
//			auto element8_16 = linear.Allocate(8, 16);
//			auto element8_32 = linear.Allocate(8, 32);
//			auto element8_64 = linear.Allocate(8, 64);
//	
//			ASSERT_TRUE(element8_1.first);
//			ASSERT_TRUE(element8_2.first);
//			ASSERT_TRUE(element8_4.first);
//			ASSERT_TRUE(element8_8.first);
//			ASSERT_FALSE(element8_16.first);
//			ASSERT_FALSE(element8_32.first);
//			ASSERT_FALSE(element8_64.first);
//	
//			ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//			ASSERT_EQ(linear.GetPagePoolSize(), 4);
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			AllocatorLinear linear(context_, 8);
//	
//			auto element4_1 = linear.Allocate(4, 1);
//			auto element4_2 = linear.Allocate(4, 2);
//			auto element4_4 = linear.Allocate(4, 4);
//			auto element4_8 = linear.Allocate(4, 8);
//			auto element4_16 = linear.Allocate(4, 16);
//			auto element4_32 = linear.Allocate(4, 32);
//	
//			ASSERT_TRUE(element4_1.first);
//			ASSERT_TRUE(element4_2.first);
//			ASSERT_TRUE(element4_4.first);
//			ASSERT_TRUE(element4_8.first);
//			ASSERT_FALSE(element4_16.first);
//			ASSERT_FALSE(element4_32.first);
//	
//			ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//			ASSERT_EQ(linear.GetPagePoolSize(), 3);
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			AllocatorLinear linear(context_, 8);
//	
//			auto element4_1 = linear.Allocate(4, 1);
//			auto element1_1 = linear.Allocate(1, 1);
//			auto element1_8 = linear.Allocate(1, 8);
//			auto element1_2 = linear.Allocate(1, 2);
//			auto element2_2 = linear.Allocate(2, 2);
//			auto element4_2 = linear.Allocate(4, 2);
//			auto element1_4 = linear.Allocate(1, 4);
//	
//			ASSERT_TRUE(element4_1.first);
//			ASSERT_TRUE(element1_1.first);
//			ASSERT_TRUE(element1_8.first);
//			ASSERT_TRUE(element1_2.first);
//			ASSERT_TRUE(element2_2.first);
//			ASSERT_TRUE(element4_2.first);
//			ASSERT_TRUE(element1_4.first);
//	
//			ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//			ASSERT_EQ(linear.GetPagePoolSize(), 4);
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			AllocatorLinear linear(context_, 8);
//	
//			auto element1_1 = linear.Allocate(1, 1);
//			auto element4_1 = linear.Allocate(4, 1);
//			auto element1_8 = linear.Allocate(1, 8);
//			auto element1_2 = linear.Allocate(1, 2);
//			auto element4_2 = linear.Allocate(4, 2);
//			auto element2_2 = linear.Allocate(2, 2);
//			auto element1_4 = linear.Allocate(1, 4);
//	
//			ASSERT_TRUE(element4_1.first);
//			ASSERT_TRUE(element1_1.first);
//			ASSERT_TRUE(element1_8.first);
//			ASSERT_TRUE(element1_2.first);
//			ASSERT_TRUE(element2_2.first);
//			ASSERT_TRUE(element4_2.first);
//			ASSERT_TRUE(element1_4.first);
//	
//			ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//			ASSERT_EQ(linear.GetPagePoolSize(), 4);
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			AllocatorLinear linear(context_, 8);
//	
//			auto element1_1 = linear.Allocate(1, 1);
//			auto element1_8 = linear.Allocate(1, 8);
//			auto element4_1 = linear.Allocate(4, 1);
//			auto element4_2 = linear.Allocate(4, 2);
//			auto element1_2 = linear.Allocate(1, 2);
//			auto element2_2 = linear.Allocate(2, 2);
//			auto element1_4 = linear.Allocate(1, 4);
//	
//			ASSERT_TRUE(element4_1.first);
//			ASSERT_TRUE(element1_1.first);
//			ASSERT_TRUE(element1_8.first);
//			ASSERT_TRUE(element1_2.first);
//			ASSERT_TRUE(element2_2.first);
//			ASSERT_TRUE(element4_2.first);
//			ASSERT_TRUE(element1_4.first);
//	
//			ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//			ASSERT_EQ(linear.GetPagePoolSize(), 4);
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			AllocatorLinear linear(context_, 8);
//	
//			auto element1_1 = linear.Allocate(1, 1);
//			auto element4_2 = linear.Allocate(4, 2);
//			auto element1_8 = linear.Allocate(1, 8);
//			auto element2_2 = linear.Allocate(2, 2);
//			auto element4_1 = linear.Allocate(4, 1);
//			auto element1_2 = linear.Allocate(1, 2);
//			auto element1_4 = linear.Allocate(1, 4);
//	
//			ASSERT_TRUE(element4_1.first);
//			ASSERT_TRUE(element1_1.first);
//			ASSERT_TRUE(element1_8.first);
//			ASSERT_TRUE(element1_2.first);
//			ASSERT_TRUE(element2_2.first);
//			ASSERT_TRUE(element4_2.first);
//			ASSERT_TRUE(element1_4.first);
//	
//			ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//			ASSERT_EQ(linear.GetPagePoolSize(), 4);
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	}
//	
//	TEST_F(Engine, DISABLED_Allocator_LinearReuseAllocation)
//	{
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			decltype(context_) error;
//	
//			AllocatorLinear linear(error, 1024);
//	
//			{
//				auto element128_1 = linear.Allocate(128, 1);
//				auto element128_2 = linear.Allocate(128, 2);
//				auto element128_4 = linear.Allocate(128, 4);
//				auto element128_8 = linear.Allocate(128, 8);
//	
//				ASSERT_FALSE(element128_1.first);
//				ASSERT_FALSE(element128_2.first);
//				ASSERT_FALSE(element128_4.first);
//				ASSERT_FALSE(element128_8.first);
//	
//				ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//				ASSERT_EQ(linear.GetPagePoolSize(), 0);
//			}
//	
//			linear.Reset();
//	
//			ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//			ASSERT_EQ(linear.GetPagePoolSize(), 0);
//	
//			{
//				auto element128_1 = linear.Allocate(128, 1);
//				auto element128_2 = linear.Allocate(128, 2);
//				auto element128_4 = linear.Allocate(128, 4);
//				auto element128_8 = linear.Allocate(128, 8);
//	
//				ASSERT_FALSE(element128_1.first);
//				ASSERT_FALSE(element128_2.first);
//				ASSERT_FALSE(element128_4.first);
//				ASSERT_FALSE(element128_8.first);
//	
//				ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//				ASSERT_EQ(linear.GetPagePoolSize(), 0);
//			}
//	
//			linear.Reset();
//	
//			ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//			ASSERT_EQ(linear.GetPagePoolSize(), 0);
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			AllocatorLinear linear(context_, 64);
//	
//			{
//				auto element64_1 = linear.Allocate(64, 1);
//				auto element128_4 = linear.Allocate(128, 4);
//				auto element64_2 = linear.Allocate(64, 2);
//				auto element128_8 = linear.Allocate(128, 8);
//	
//				ASSERT_TRUE(element64_1.first);
//				ASSERT_TRUE(element64_2.first);
//				ASSERT_FALSE(element128_4.first);
//				ASSERT_FALSE(element128_8.first);
//	
//				ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//				ASSERT_EQ(linear.GetPagePoolSize(), 2);
//			}
//	
//			linear.Reset();
//	
//			ASSERT_EQ(linear.GetPageAvailableSize(), 2);
//			ASSERT_EQ(linear.GetPagePoolSize(), 2);
//	
//			{
//				auto element64_1 = linear.Allocate(64, 1);
//				auto element128_4 = linear.Allocate(128, 4);
//				auto element64_2 = linear.Allocate(64, 2);
//				auto element128_8 = linear.Allocate(128, 8);
//	
//				ASSERT_TRUE(element64_1.first);
//				ASSERT_TRUE(element64_2.first);
//				ASSERT_FALSE(element128_4.first);
//				ASSERT_FALSE(element128_8.first);
//	
//				ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//				ASSERT_EQ(linear.GetPagePoolSize(), 2);
//			}
//	
//			linear.Reset();
//	
//			ASSERT_EQ(linear.GetPageAvailableSize(), 2);
//			ASSERT_EQ(linear.GetPagePoolSize(), 2);
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			AllocatorLinear linear(context_, 32);
//	
//			{
//				auto element32_1 = linear.Allocate(32, 1);
//				auto element16_2 = linear.Allocate(16, 2);
//				auto element32_4 = linear.Allocate(32, 4);
//				auto element16_8 = linear.Allocate(16, 8);
//				auto element16_16 = linear.Allocate(16, 16);
//	
//				ASSERT_TRUE(element32_1.first);
//				ASSERT_TRUE(element16_2.first);
//				ASSERT_TRUE(element32_4.first);
//				ASSERT_TRUE(element16_8.first);
//				ASSERT_TRUE(element16_16.first);
//	
//				ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//				ASSERT_EQ(linear.GetPagePoolSize(), 4);
//			}
//	
//			linear.Reset();
//	
//			ASSERT_EQ(linear.GetPageAvailableSize(), 4);
//			ASSERT_EQ(linear.GetPagePoolSize(), 4);
//	
//			{
//				auto element32_1 = linear.Allocate(32, 1);
//				auto element16_2 = linear.Allocate(16, 2);
//				auto element32_4 = linear.Allocate(32, 4);
//				auto element16_8 = linear.Allocate(16, 8);
//				auto element16_16 = linear.Allocate(16, 16);
//	
//				ASSERT_TRUE(element32_1.first);
//				ASSERT_TRUE(element16_2.first);
//				ASSERT_TRUE(element32_4.first);
//				ASSERT_TRUE(element16_8.first);
//				ASSERT_TRUE(element16_16.first);
//	
//				ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//				ASSERT_EQ(linear.GetPagePoolSize(), 4);
//			}
//	
//			linear.Reset();
//	
//			ASSERT_EQ(linear.GetPageAvailableSize(), 4);
//			ASSERT_EQ(linear.GetPagePoolSize(), 4);
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			AllocatorLinear linear(context_, 256);
//	
//			{
//				auto element16_16 = linear.Allocate(16, 16);
//				auto element32_32 = linear.Allocate(32, 32);
//				auto element64_64 = linear.Allocate(64, 64);
//				auto element128_128 = linear.Allocate(128, 128);
//				auto element256_256 = linear.Allocate(256, 256);
//	
//				ASSERT_TRUE(element16_16.first);
//				ASSERT_TRUE(element32_32.first);
//				ASSERT_TRUE(element64_64.first);
//				ASSERT_TRUE(element128_128.first);
//				ASSERT_TRUE(element256_256.first);
//	
//				ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//				ASSERT_EQ(linear.GetPagePoolSize(), 2);
//			}
//	
//			linear.Reset();
//	
//			ASSERT_EQ(linear.GetPageAvailableSize(), 2);
//			ASSERT_EQ(linear.GetPagePoolSize(), 2);
//	
//			{
//				auto element16_16 = linear.Allocate(16, 16);
//				auto element32_32 = linear.Allocate(32, 32);
//				auto element64_64 = linear.Allocate(64, 64);
//				auto element128_128 = linear.Allocate(128, 128);
//				auto element256_256 = linear.Allocate(256, 256);
//	
//				ASSERT_TRUE(element16_16.first);
//				ASSERT_TRUE(element32_32.first);
//				ASSERT_TRUE(element64_64.first);
//				ASSERT_TRUE(element128_128.first);
//				ASSERT_TRUE(element256_256.first);
//	
//				ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//				ASSERT_EQ(linear.GetPagePoolSize(), 2);
//			}
//	
//			linear.Reset();
//	
//			ASSERT_EQ(linear.GetPageAvailableSize(), 2);
//			ASSERT_EQ(linear.GetPagePoolSize(), 2);
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			AllocatorLinear linear(context_, 8);
//	
//			{
//				auto element8_1 = linear.Allocate(8, 1);
//				auto element8_2 = linear.Allocate(8, 2);
//				auto element8_4 = linear.Allocate(8, 4);
//				auto element8_8 = linear.Allocate(8, 8);
//				auto element8_16 = linear.Allocate(8, 16);
//				auto element8_32 = linear.Allocate(8, 32);
//				auto element8_64 = linear.Allocate(8, 64);
//	
//				ASSERT_TRUE(element8_1.first);
//				ASSERT_TRUE(element8_2.first);
//				ASSERT_TRUE(element8_4.first);
//				ASSERT_TRUE(element8_8.first);
//				ASSERT_FALSE(element8_16.first);
//				ASSERT_FALSE(element8_32.first);
//				ASSERT_FALSE(element8_64.first);
//	
//				ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//				ASSERT_EQ(linear.GetPagePoolSize(), 4);
//			}
//	
//			linear.Reset();
//	
//			ASSERT_EQ(linear.GetPageAvailableSize(), 4);
//			ASSERT_EQ(linear.GetPagePoolSize(), 4);
//	
//			{
//				auto element4_1 = linear.Allocate(4, 1);
//				auto element1_1 = linear.Allocate(1, 1);
//				auto element1_8 = linear.Allocate(1, 8);
//				auto element1_2 = linear.Allocate(1, 2);
//				auto element2_2 = linear.Allocate(2, 2);
//				auto element4_2 = linear.Allocate(4, 2);
//				auto element1_4 = linear.Allocate(1, 4);
//	
//				ASSERT_TRUE(element4_1.first);
//				ASSERT_TRUE(element1_1.first);
//				ASSERT_TRUE(element1_8.first);
//				ASSERT_TRUE(element1_2.first);
//				ASSERT_TRUE(element2_2.first);
//				ASSERT_TRUE(element4_2.first);
//				ASSERT_TRUE(element1_4.first);
//	
//				ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//				ASSERT_EQ(linear.GetPagePoolSize(), 4);
//			}
//	
//			linear.Reset();
//	
//			ASSERT_EQ(linear.GetPageAvailableSize(), 4);
//			ASSERT_EQ(linear.GetPagePoolSize(), 4);
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			AllocatorLinear linear(context_, 8);
//	
//			{
//				auto element1_1 = linear.Allocate(1, 1);
//				auto element1_8 = linear.Allocate(1, 8);
//				auto element4_1 = linear.Allocate(4, 1);
//				auto element4_2 = linear.Allocate(4, 2);
//				auto element1_2 = linear.Allocate(1, 2);
//				auto element2_2 = linear.Allocate(2, 2);
//				auto element1_4 = linear.Allocate(1, 4);
//	
//				ASSERT_TRUE(element4_1.first);
//				ASSERT_TRUE(element1_1.first);
//				ASSERT_TRUE(element1_8.first);
//				ASSERT_TRUE(element1_2.first);
//				ASSERT_TRUE(element2_2.first);
//				ASSERT_TRUE(element4_2.first);
//				ASSERT_TRUE(element1_4.first);
//	
//				ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//				ASSERT_EQ(linear.GetPagePoolSize(), 4);
//			}
//	
//			linear.Reset();
//	
//			ASSERT_EQ(linear.GetPageAvailableSize(), 4);
//			ASSERT_EQ(linear.GetPagePoolSize(), 4);
//	
//			{
//				auto element1_1 = linear.Allocate(1, 1);
//				auto element4_2 = linear.Allocate(4, 2);
//				auto element1_8 = linear.Allocate(1, 8);
//				auto element2_2 = linear.Allocate(2, 2);
//				auto element4_1 = linear.Allocate(4, 1);
//				auto element1_2 = linear.Allocate(1, 2);
//				auto element1_4 = linear.Allocate(1, 4);
//	
//				ASSERT_TRUE(element4_1.first);
//				ASSERT_TRUE(element1_1.first);
//				ASSERT_TRUE(element1_8.first);
//				ASSERT_TRUE(element1_2.first);
//				ASSERT_TRUE(element2_2.first);
//				ASSERT_TRUE(element4_2.first);
//				ASSERT_TRUE(element1_4.first);
//	
//				ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//				ASSERT_EQ(linear.GetPagePoolSize(), 4);
//			}
//	
//			linear.Reset();
//	
//			ASSERT_EQ(linear.GetPageAvailableSize(), 4);
//			ASSERT_EQ(linear.GetPagePoolSize(), 4);
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			AllocatorLinear linear(context_, 64);
//	
//			{
//				auto element64_1 = linear.Allocate(64, 1);
//				auto element128_4 = linear.Allocate(128, 4);
//				auto element64_2 = linear.Allocate(64, 2);
//				auto element128_8 = linear.Allocate(128, 8);
//	
//				ASSERT_TRUE(element64_1.first);
//				ASSERT_TRUE(element64_2.first);
//				ASSERT_FALSE(element128_4.first);
//				ASSERT_FALSE(element128_8.first);
//	
//				ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//				ASSERT_EQ(linear.GetPagePoolSize(), 2);
//			}
//	
//			linear.Reset();
//	
//			ASSERT_EQ(linear.GetPageAvailableSize(), 2);
//			ASSERT_EQ(linear.GetPagePoolSize(), 2);
//	
//			{
//				auto element32_1 = linear.Allocate(32, 1);
//				auto element16_2 = linear.Allocate(16, 2);
//				auto element32_4 = linear.Allocate(32, 4);
//				auto element16_8 = linear.Allocate(16, 8);
//				auto element16_16 = linear.Allocate(16, 16);
//	
//				ASSERT_TRUE(element32_1.first);
//				ASSERT_TRUE(element16_2.first);
//				ASSERT_TRUE(element32_4.first);
//				ASSERT_TRUE(element16_8.first);
//				ASSERT_TRUE(element16_16.first);
//	
//				ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//				ASSERT_EQ(linear.GetPagePoolSize(), 2);
//			}
//	
//			linear.Reset();
//	
//			ASSERT_EQ(linear.GetPageAvailableSize(), 2);
//			ASSERT_EQ(linear.GetPagePoolSize(), 2);
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	}
//	
//	TEST_F(Engine, Allocator_ListBasicAllocation)
//	{
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			decltype(context_) error;
//	
//			AllocatorList list(error, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 4);
//	
//			auto element1 = list.Allocate(1);
//			auto element2 = list.Allocate(2);
//			auto element4 = list.Allocate(4);
//			auto element8 = list.Allocate(8);
//	
//			ASSERT_FALSE(element1.IsValid());
//			ASSERT_FALSE(element2.IsValid());
//			ASSERT_FALSE(element4.IsValid());
//			ASSERT_FALSE(element8.IsValid());
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			AllocatorList list(context_, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 4);
//	
//			auto element1 = list.Allocate(1);
//			auto element2 = list.Allocate(2);
//			auto element4 = list.Allocate(4);
//			auto element8 = list.Allocate(8);
//	
//			ASSERT_TRUE(element1.IsValid());
//			ASSERT_TRUE(element2.IsValid());
//			ASSERT_TRUE(element4.IsValid());
//			ASSERT_TRUE(element8.IsValid());
//	
//			ASSERT_EQ(element1.GetDescCount(), 1);
//			ASSERT_EQ(element2.GetDescCount(), 2);
//			ASSERT_EQ(element4.GetDescCount(), 4);
//			ASSERT_EQ(element8.GetDescCount(), 8);
//	
//			return;
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	//	
//	//	{
//	//		AllocatorLinear linear(context_, 32);
//	//	
//	//		auto element32_1 = linear.Allocate(32, 1);
//	//		auto element16_2 = linear.Allocate(16, 2);
//	//		auto element32_4 = linear.Allocate(32, 4);
//	//		auto element16_8 = linear.Allocate(16, 8);
//	//		auto element16_16 = linear.Allocate(16, 16);
//	//	
//	//		ASSERT_TRUE(element32_1.first);
//	//		ASSERT_TRUE(element16_2.first);
//	//		ASSERT_TRUE(element32_4.first);
//	//		ASSERT_TRUE(element16_8.first);
//	//		ASSERT_TRUE(element16_16.first);
//	//	
//	//		ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//	//		ASSERT_EQ(linear.GetPagePoolSize(), 4);
//	//	}
//	//	
//	//	////////////////////////////////////////////////////////////////////////////////
//	//	
//	//	{
//	//		AllocatorLinear linear(context_, 1024);
//	//	
//	//		auto element128_16 = linear.Allocate(128, 16);
//	//		auto element128_32 = linear.Allocate(128, 32);
//	//		auto element128_64 = linear.Allocate(128, 64);
//	//		auto element128_128 = linear.Allocate(128, 128);
//	//		auto element256_256 = linear.Allocate(256, 256);
//	//		auto element256_128 = linear.Allocate(256, 128);
//	//		auto element256_64 = linear.Allocate(256, 64);
//	//		auto element256_32 = linear.Allocate(256, 32);
//	//		auto element256_16 = linear.Allocate(256, 16);
//	//	
//	//		ASSERT_TRUE(element128_16.first);
//	//		ASSERT_TRUE(element128_32.first);
//	//		ASSERT_TRUE(element128_64.first);
//	//		ASSERT_TRUE(element128_128.first);
//	//		ASSERT_TRUE(element256_16.first);
//	//		ASSERT_TRUE(element256_32.first);
//	//		ASSERT_TRUE(element256_64.first);
//	//		ASSERT_TRUE(element256_128.first);
//	//		ASSERT_TRUE(element256_256.first);
//	//	
//	//		ASSERT_EQ(linear.GetPageAvailableSize(), 0);
//	//		ASSERT_EQ(linear.GetPagePoolSize(), 2);
//	//	}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	}