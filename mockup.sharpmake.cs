using Sharpmake;
using System;
//using System.Data;
//using System.Diagnostics;

[module: Sharpmake.Include("custom.sharpmake.cs")]

namespace Mockup
{
	//	[Sharpmake.Generate]
	//	class aftermath : CustomLibrary
	//	{
	//	    public aftermath()
	//	    {
	//	        SourceRootPath = @"[project.SharpmakeCsPath]\external\aftermath";
	//	    }
	//	
	//	    public override void Configure(Configuration conf, CustomTarget target)
	//	    {
	//	        base.Configure(conf, target);
	//	
	//	        conf.LibraryPaths.Add(@"[project.SourceRootPath]\lib\x64");
	//	        conf.IncludePaths.Add(@"[project.SourceRootPath]\include");
	//	        conf.IncludePaths.Add(@"[project.SourceRootPath]");
	//	
	//	        conf.LibraryFiles.Add("GFSDK_Aftermath_Lib.x64.lib");
	//	        conf.TargetCopyFiles.Add(@"[project.SourceRootPath]\lib\x64\GFSDK_Aftermath_Lib.x64.dll");
	//	    }
	//	}

	//	[Sharpmake.Generate]
	//	class simdjson : CustomLibrary
	//	{
	//		public simdjson()
	//		{
	//			SourceRootPath = @"[project.SharpmakeCsPath]\external\simdjson";
	//			SourceFiles.Add(@"[project.SharpmakeCsPath]\external\simdjson\src\simdjson.cpp");
	//		}
	//	
	//		public override void Configure(Configuration conf, CustomTarget target)
	//		{
	//			base.Configure(conf, target);
	//			
	//			conf.IncludePaths.Add(@"[project.SharpmakeCsPath]\external\simdjson\include");
	//			conf.IncludePaths.Add(@"[project.SourceRootPath]");
	//		}
	//	}	

	[Sharpmake.Generate]
	class googletest : CustomLibrary
	{
		public googletest()
		{
			SourceRootPath = @"[project.SharpmakeCsPath]\tools\googletest\googletest";
			SourceFilesExcludeRegex.Add(@"\\samples");
			SourceFilesExcludeRegex.Add(@"\\test");
			SourceFilesExcludeRegex.Add(@"gtest-all.cc");
		}
	
		public override void Configure(Configuration conf, CustomTarget target)
		{
			base.Configure(conf, target);
			
			conf.Defines.Add("GTEST_ENABLE_CATCH_EXCEPTIONS_=1");
			conf.Defines.Add("gtest_build_tests=OFF");
			conf.Defines.Add("gtest_build_samples=OFF");
			
			//conf.IncludePaths.Add(@"[project.SharpmakeCsPath]\tools\googletest\googletest");
			conf.IncludePaths.Add(@"[project.SharpmakeCsPath]\tools\googletest\googletest\include");
		}
	}	

    ////////////////////////////////////////////////////////////////////////////////

    [Sharpmake.Generate]
	class core : CustomLibrary
    {
		public core()
		{
			SourceRootPath = @"[project.SharpmakeCsPath]\source\core";
			
			//simdjson
			//SourceFiles.Add(@"[project.SharpmakeCsPath]\external\simdjson\src\simdjson.cpp");
			//SourceFiles.Add(@"[project.SharpmakeCsPath]\external\simdjson\include\simdjson.h");
			
			//cista
			//SourceFiles.Add(@"[project.SharpmakeCsPath]\external\cista\include\cista\serialization.h");
		}
		
		public override void Configure(Configuration conf, CustomTarget target)
		{
			base.Configure(conf, target);

			//simdjson
			//conf.IncludePaths.Add(@"[project.SharpmakeCsPath]\external\simdjson\include");
			//conf.IncludePaths.Add(@"[project.SharpmakeCsPath]\external\simdjson\src");
					
			//cista
			//conf.IncludePaths.Add(@"[project.SharpmakeCsPath]\external\cista\include");
			conf.LibraryFiles.Add("dbghelp.lib");
		}
    }
	
    [Sharpmake.Generate]
	class gltf : CustomLibrary
    {
		public gltf()
		{
			SourceRootPath = @"[project.SharpmakeCsPath]\source\gltf";
			
			//simdjson
			SourceFiles.Add(@"[project.SharpmakeCsPath]\external\simdjson\src\simdjson.cpp");
			SourceFiles.Add(@"[project.SharpmakeCsPath]\external\simdjson\include\simdjson.h");
		}
		
		public override void Configure(Configuration conf, CustomTarget target)
		{
			base.Configure(conf, target);

			//simdjson
			conf.IncludePaths.Add(@"[project.SharpmakeCsPath]\external\simdjson\include");
			conf.IncludePaths.Add(@"[project.SharpmakeCsPath]\external\simdjson\src");
		}
    }	

	[Sharpmake.Generate]
	class engine : CustomLibrary
	{
		public engine()
		{
			SourceRootPath = @"[project.SharpmakeCsPath]\source\engine";
        }

		public override void Configure(Configuration conf, CustomTarget target)
		{
			base.Configure(conf, target);
	
			conf.AddPrivateDependency<core>(target);
			//conf.AddPublicDependency<aftermath>(target);

			//TODO: debug
			conf.LibraryPaths.Add(@"\external\xcompiler\build\release\lib");

			conf.TargetCopyFiles.Add(KitsRootPaths.GetRoot(KitsRootEnum.KitsRoot10) + @"bin\10.0.19041.0\x64\dxil.dll");
			conf.TargetCopyFiles.Add(@"\external\xcompiler\build\release\bin\dxcompiler.dll");

			conf.LibraryFiles.Add("dxgi.lib");
			conf.LibraryFiles.Add("d3d12.lib");
			conf.LibraryFiles.Add("dxguid.lib");
			conf.LibraryFiles.Add("dxcompiler.lib");
        }
	}

	////////////////////////////////////////////////////////////////////////////////

	[Sharpmake.Generate]
	class _editor : CustomProgram
	{
		public _editor()
		{
			SourceRootPath = @"[project.SharpmakeCsPath]\source\editor";

			SourceFiles.Add(@"[project.SharpmakeCsPath]\external\imgui\imconfig.h");
			SourceFiles.Add(@"[project.SharpmakeCsPath]\external\imgui\imgui_internal.h");
			SourceFiles.Add(@"[project.SharpmakeCsPath]\external\imgui\imstb_rectpack.h");
			SourceFiles.Add(@"[project.SharpmakeCsPath]\external\imgui\imstb_textedit.h");
			SourceFiles.Add(@"[project.SharpmakeCsPath]\external\imgui\imstb_truetype.h");
			SourceFiles.Add(@"[project.SharpmakeCsPath]\external\imgui\imgui.h");
			SourceFiles.Add(@"[project.SharpmakeCsPath]\external\imgui\imgui.cpp");
			SourceFiles.Add(@"[project.SharpmakeCsPath]\external\imgui\imgui_draw.cpp");
			SourceFiles.Add(@"[project.SharpmakeCsPath]\external\imgui\imgui_widgets.cpp");
			SourceFiles.Add(@"[project.SharpmakeCsPath]\external\imgui\imgui_tables.cpp");
			SourceFiles.Add(@"[project.SharpmakeCsPath]\external\imgui\backends\imgui_impl_win32.h");
			SourceFiles.Add(@"[project.SharpmakeCsPath]\external\imgui\backends\imgui_impl_win32.cpp");
			SourceFiles.Add(@"[project.SharpmakeCsPath]\external\imgui\imgui_demo.cpp");

			ResourceFiles.Add(@"[project.SharpmakeCsPath]\source\core\platform\resources.rc");
		}
	
		public override void Configure(Configuration conf, CustomTarget target)
		{
			base.Configure(conf, target);

			conf.AddPrivateDependency<core>(target);
			conf.AddPrivateDependency<engine>(target);
			conf.AddPrivateDependency<gltf>(target);

			conf.IncludePrivatePaths.Add(@"[project.SharpmakeCsPath]\external\imgui");

			conf.VcxprojUserFile.LocalDebuggerWorkingDirectory = @"[project.SharpmakeCsPath]\workdir";
		}
	}
	
	////////////////////////////////////////////////////////////////////////////////

	[Sharpmake.Generate]
	class _tests : CustomProgram
	{
		public _tests()
		{
			SourceRootPath = @"[project.SharpmakeCsPath]\workbench\tests";
			
			//SourceFiles.Add(@"[project.SharpmakeCsPath]\tools\googletest\googletest\src\gtest.cc");
			//SourceFiles.Add(@"[project.SharpmakeCsPath]\tools\googletest\googletest\src\gtest_main.cc");
			//SourceFiles.Add(@"[project.SharpmakeCsPath]\tools\googletest\googletest\src\gtest-all.cc");	
        }
		
		public override void Configure(Configuration conf, CustomTarget target)
		{
			base.Configure(conf, target);
			
			conf.Options.Add(Options.Vc.Linker.SubSystem.Console);
			
			conf.AddPrivateDependency<core>(target);
			conf.AddPrivateDependency<gltf>(target);
			conf.AddPrivateDependency<googletest>(target);
						
			//conf.Defines.Add("GTEST_ENABLE_CATCH_EXCEPTIONS_=1");	
			//conf.IncludePaths.Add(@"[project.SharpmakeCsPath]\tools\googletest\googletest");
			//conf.IncludePaths.Add(@"[project.SharpmakeCsPath]\tools\googletest\googletest\include");
			
			conf.VcxprojUserFile.LocalDebuggerWorkingDirectory = @"[project.SharpmakeCsPath]\workdir";
		}
	}
	
//	[Sharpmake.Generate]
//	class _benchmarks : CustomProgram
//	{
//		public _benchmarks()
//		{
//			SourceRootPath = @"[project.SharpmakeCsPath]\workbench\benchmarks";
//		}
//		
//		public override void Configure(Configuration conf, CustomTarget target)
//		{
//			base.Configure(conf, target);
//		}
//	}
	
	////////////////////////////////////////////////////////////////////////////////

	[Sharpmake.Generate]
	class mockup : CustomSolution
    {
		public override void Configure(Configuration conf, CustomTarget target)
        {
			base.Configure(conf, target);

			conf.AddProject<_editor>(target);
			conf.AddProject<_tests>(target);
			//conf.AddProject<_benchmarks>(target);
        }
	}

	public static class Bootstrap
	{
		[Sharpmake.Main]
		public static void SharpmakeMain(Sharpmake.Arguments arguments)
		{
			arguments.Generate<mockup>();
		}
	}
}