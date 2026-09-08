local application_name = "C-Utils";
local application_version = "2026-09-08";
local application_standards =
{
	"c90",
	"c++98",
};
local commands =
{
	"help",
	"test",
	"clean"
};

local compilers =
{
	os.getenv("CC") or "clang",
	os.getenv("CXX") or os.getenv("CC") or "clang++"
};

local include = "-Iinclude -I/usr/include/libpng16 -I/opt/homebrew/include -I/ucrt64/include/libpng16 -I/ucrt64/include";

local flags =
{
	{},
	{
		"-fdiagnostics-color=always",
		"-std=" .. application_standards[2],
		"-Wall",
		"-Wextra",
		"-Wpedantic",
		"-Wshadow",
		"-Wconversion",
		"-Wsign-conversion",
		"-Wformat=2",
		"-Wnull-dereference",
		"-Wcast-align",
		"-Wpointer-arith",
		"-Wundef",
		"-Wno-long-long",
		"-Oz",
		"-funroll-loops",
		"-fstack-protector-strong",
		"-v"
	}
};

for i = 1, #flags[2] do
	table.insert(flags[1], flags[2][i]);
end

flags[1][2] = "-std=" .. application_standards[1];

table.insert(flags[1], "-Wstrict-prototypes");
table.insert(flags[1], "-Wmissing-prototypes");

local sources =
{
	"source/C-Utils/consts.c",
	"source/C-Utils/c-utils.c",
	"source/C-Utils/big-data.c",
	"source/C-Utils/img-utls.c",
	"source/C-Utils/mth-utls.c",
	"source/C-Utils/tmp-utls.c",
	"source/C-Utils/trd-utls.c",
	"source/C-Utils/cryptrnd.c",
};

local function help()
	io.write("App name: " .. application_name .. "\n");
	io.write("App version: " .. application_version .. "\n");
	io.write("App standards: " .. table.concat(application_standards, ", ") .. "\n");
	io.write("Commands: " .. table.concat(commands, ", ") .. "\n");
end

local function test()
	local sys = os.getenv("OS");

	if sys == "Windows_NT" then
		os.execute("if not exist build mkdir build");

		os.execute(compilers[1] .. " " .. table.concat(sources, " ") .. " " .. table.concat(flags[1], " ") .. " " .. include .. " -c");
		os.execute("move *.o build\\ 2>nul");
		os.execute("dir build");

		os.execute(compilers[2] .. " -x c++ " .. table.concat(sources, " ") .. " " .. table.concat(flags[2], " ") .. " " .. include .. " -c");
		os.execute("move *.o build\\ 2>nul");
		os.execute("dir build");
	else
		os.execute("mkdir -p build");

		os.execute(compilers[1] .. " " .. table.concat(sources, " ") .. " " .. table.concat(flags[1], " ") .. " " .. include .. " -c");
		os.execute("mv *.o build/ 2>/dev/null");
		os.execute("ls -la build");

		os.execute(compilers[2] .. " -x c++ " .. table.concat(sources, " ") .. " " .. table.concat(flags[2], " ") .. " " .. include .. " -c");
		os.execute("mv *.o build/ 2>/dev/null");
		os.execute("ls -la build");
	end
end

local function clean()
	local sys = os.getenv("OS");

	if sys == "Windows_NT" then
		os.execute("if exist build rd /s /q build");
	else
		os.execute("rm -rf build");
	end
end

local function main()
	if #arg == 0 then
		help();
	elseif #arg >= 1 then
		if arg[1] == "help" then
			help();
		elseif arg[1] == "test" then
			test();
		elseif arg[1] == "clean" then
			clean();
		end
	end

	return 0;
end

os.exit(main(), true);
