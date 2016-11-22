#!/usr/bin/ruby

unless File.exists?('/tmp/RakeBuilder.rb')
  system('wget https://raw.githubusercontent.com/chaos0x8/rake-builder/master/lib/RakeBuilder.rb -O /tmp/RakeBuilder.rb', err: '/dev/null')
end

require '/tmp/RakeBuilder.rb'

apps = Dir['*.cpp'].collect { |fn|
  Executable.new { |t|
    t.name = "bin/#{File.basename(fn)[0..-5]}"
    t.sources = [fn]
    t.flags = [ '--std=c++14', '-pthread' ]
    t.libs = [ '-lgtest', '-lgmock' ]
  }
}

desc 'Compiles all examples'
multitask(default: RakeBuilder::Names[apps])

desc 'Compiles and runs all examples'
task(run: :default) {
  apps.each { |app|
    sh app.name
  }
}

desc 'Cleans objects, libs and executables'
task(:clean) {
  sh "rm -rf .obj" if File.directory?('.obj')
  sh "rm -rf bin" if File.directory?('bin')
}
