void main(MultiBuild::Workspace& workspace) {	
	auto project = workspace.create_project(".");
	auto properties = project.properties();

	project.name("spdlog");
	properties.binary_object_kind(MultiBuild::BinaryObjectKind::eStaticLib);
	project.license("./LICENSE");

	project.project_includes({
		"fmt"
	});

	project.include_own_required_includes(true);
	project.add_required_project_include({
		"./include"
	});

	properties.files({
		"./include/**.h",
		"./src/**.cpp"
	});

	properties.excluded_files({
		"./src/bundled_fmtlib_format.cpp"
	});

	properties.defines("SPDLOG_COMPILED_LIB");
	
	{
		MultiBuild::ScopedFilter _(workspace, "project.compiler:VisualCpp");
		properties.disable_warnings("4146");
	}
}